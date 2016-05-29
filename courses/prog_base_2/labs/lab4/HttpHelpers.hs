module HttpHelpers where

import Magic

import System.IO
import System.Directory
import Control.Monad
import Control.Applicative
import Data.List

import qualified Data.ByteString as B
import qualified Data.ByteString.Char8 as C
import Data.ByteString.UTF8(fromString,toString)

data Method = GET | POST | DELETE deriving (Show)

ctJSONutf8 = ("Content-Type", "application/json; charset=utf-8")

badRequestPage::Handle->IO ()
badRequestPage hdl = do
    hPutStr hdl "HTTP/1.1 400 Bad Request\r\n\
                \Content-Length: 10\r\n\
                \\r\n\
                \Bad request"
    hClose hdl               

createResponseHead::String->[(String, String)]->String
createResponseHead status headers = status ++ crlf ++ headerText ++ crlf
  where crlf = "\r\n"
        headerPair (name, value) = name ++ ": "++value
        foldF accum nextPair = accum ++ (headerPair nextPair) ++ crlf
        headerText = foldl foldF "" headers

createResponseString::String->[(String, String)]->String->String
createResponseString status headersNoCL body =
  (createResponseHead status headers) ++ body
  where
    cl = show $ B.length (fromString body)
    headers = [("Content-Length",cl)] ++ headersNoCL

createResponse::String->[(String,String)]->String->C.ByteString
createResponse status headers body =
  fromString $ createResponseString status headers body

createJSONResponse = createResponse "HTTP/1.1 200 OK" [ctJSONutf8]

sendJSON = (. createJSONResponse) . C.hPutStr

pageNotFound::Handle->IO ()
pageNotFound hdl = do
  C.hPutStr hdl $ createResponse "HTTP/1.1 404 Page Not Found" [] "404!"
  hClose hdl

getMimeType::Magic->FilePath->IO String
getMimeType magic path = do
  case guessedByExtension of
    Just (_,res) -> return res
    Nothing -> magicFile magic path
  where    
    knownTypes = [(".css","text/css"),(".js","application/javascript")]
    guessedByExtension = find (\(ext,_) -> isSuffixOf ext path) knownTypes
    

createStaticServer::FilePath->IO (FilePath->Handle-> IO ())
createStaticServer path = do
  magic <- magicOpen [MagicMime]
  magicLoadDefault magic
  return $ serveFunc magic
  where
    serveFunc magic relFile hdl = do
      let file = path ++ "/" ++ relFile
      fileExists <- doesFileExist file
      if not fileExists
        then pageNotFound hdl
        else do
        mimeType <- getMimeType magic file
        fileHandle <- openFile file ReadMode
        fileContent <- B.hGetContents fileHandle
        let respStart =
              createResponseHead "HTTP/1.1 200 OK"
              [("Content-Length",show $ B.length fileContent),
               ("Content-type", mimeType)]
        B.hPut hdl $ B.concat [C.pack respStart, fileContent]
        hClose hdl
                    

findContentLength::B.ByteString->Maybe Int
findContentLength message = fmap fst (byteNumberStr >>= C.readInt)
  where
    (_,headerStart) = B.breakSubstring (C.pack "Content-Length: ") message
    (headerText, _) = B.breakSubstring (C.pack "\r\n") headerStart
    value_index = fmap (+1) pindex where
      pindex = C.elemIndexEnd ' ' headerText
    byteNumberStr = fmap B.drop value_index <*> pure headerText

parseRequestURI::B.ByteString -> [String]
parseRequestURI message = map toString $ C.split '/' uriText
  where
    --URI contains first '/' in all request
    (_, uriStart) = B.breakSubstring (C.pack "/") message
    --And ends with ' ' before HTTP version
    (uriText, _) = B.breakSubstring (C.pack " ") (C.drop 1 uriStart)

parseRequestBody::B.ByteString -> String
parseRequestBody message = toString $ C.drop 4 pre_body
  where
    pre_body = snd $ B.breakSubstring (C.pack "\r\n\r\n") message

parseRequestMethod::B.ByteString -> Maybe Method
parseRequestMethod message = case getMethod message of
  "GET" -> Just GET
  "POST" -> Just POST
  "DELETE" -> Just DELETE
  _ -> Nothing
  --Method is the beginning of req line and ends with ' '
  where getMethod = toString . fst . B.breakSubstring (C.pack " ")
