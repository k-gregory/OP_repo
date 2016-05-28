module HttpHelpers where

import qualified Data.ByteString as B
import qualified Data.ByteString.Char8 as C

data Method = GET | POST | DELETE deriving (Show)

findContentLength::B.ByteString->Maybe Int
findContentLength message = fmap fst (byteNumberStr >>= C.readInt)
  where
    (_,headerStart) = B.breakSubstring (C.pack "Content-Length: ") message
    (headerText, _) = B.breakSubstring (C.pack "\r\n") headerStart
    value_index = fmap (+1) pindex where
      pindex = C.elemIndexEnd ' ' headerText
    byteNumberStr = fmap B.drop value_index <*> pure headerText

parseRequestURI::B.ByteString -> [String]
parseRequestURI message = map C.unpack $ C.split '/' uriText
  where
    --URI contains first '/' in all request
    (_, uriStart) = B.breakSubstring (C.pack "/") message
    --And ends with ' ' before HTTP version
    (uriText, _) = B.breakSubstring (C.pack " ") (C.drop 1 uriStart)

parseRequestBody::B.ByteString -> String
parseRequestBody message = C.unpack $ C.drop 4 pre_body
  where
    pre_body = snd $ B.breakSubstring (C.pack "\r\n\r\n") message

parseRequestMethod::B.ByteString -> Maybe Method
parseRequestMethod message = case getMethod message of
  "GET" -> Just GET
  "POST" -> Just POST
  "DELETE" -> Just DELETE
  _ -> Nothing
  --Method is the beginning of req line and ends with ' '
  where getMethod = C.unpack . fst . B.breakSubstring (C.pack " ")
