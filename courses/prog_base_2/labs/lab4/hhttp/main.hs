module Main where

import Network
import Network.Socket.ByteString
import Control.Concurrent
import Control.Concurrent.MVar
import Control.Applicative
import Control.Monad
import System.IO
import Text.JSON
import qualified Data.ByteString as B
import qualified Data.ByteString.Char8 as C

data Driver = Driver {
  index :: Int,
  name :: String,
  workStartDate :: String,
  satisfiedClients :: Int,
  averageSpeed :: Double,
  kmFare :: Double
                     }

type State = MVar (Int, [Driver])

(!) :: (JSON a) => JSObject JSValue -> String -> Result a
(!) = flip valFromObj

instance JSON Driver where
  showJSON d =
    makeObj [
    ("name" , showJSON $ name d),
    ("workStartDate" , showJSON $ workStartDate d),
    ("satisfiedClients" , showJSON $ satisfiedClients d),
    ("averageSpeed" , showJSON $ averageSpeed d),
    ("kmFare" , showJSON $ kmFare d)
            ]
  readJSON (JSObject obj) =
    Driver 0<$>
    obj ! "name" <*>
    obj ! "workStartDate" <*>
    obj ! "satisfiedClients" <*>
    obj ! "averageSpeed" <*>
    obj ! "kmFare"
  readJSON _ = mzero

data Method = GET | POST | DELETE deriving (Show)

driverOwnPage:: Driver->Handle->IO ()
driverOwnPage driver hdl = do
  hPutStr hdl $ "HTTP/1.1 200 OK\r\n\
                \Content-Length: " ++ (show (length $ encode driver))++"\r\n\
                \\r\n" ++encode driver
  hClose hdl

badRequestPage::Handle->IO ()
badRequestPage hdl = do
    hPutStr hdl "HTTP/1.1 400 Bad Request\r\n\
                \Content-Length: 10\r\n\
                \\r\n\
                \Bad request"
    hClose hdl

indexPage::Handle->IO ()
indexPage hdl = do
    hPutStr hdl "HTTP/1.1 200 OK\r\n\
                \Content-Length: 10\r\n\
                \\r\n\
                \Index page"
    hClose hdl
  

indexRoutes state cl GET [] = indexPage 
indexRoutes state cl method ("api" : other) = apiRoutes state cl method other
apiRoutes state cl method ("drivers" : other)  = driverRoutes state cl method other 
driverRoutes state cl GET [] hdl  = indexPage hdl
driverRoutes state cl GET [_id] hdl = do
  (maxID, drivers) <- takeMVar state
  putMVar state (maxID, drivers)
  let
    wanted_id = read _id :: Int
    driver = head $ filter (\d -> index d == wanted_id) drivers
    in driverOwnPage driver hdl

findContentLength::B.ByteString->Maybe Int
findContentLength message= fmap fst (byteNumberStr >>= C.readInt)
  where
    (_,headerStart) = B.breakSubstring (C.pack "Content-Length: ") message
    (headerText, _) = B.breakSubstring (C.pack "\r\n") headerStart
    vindex =fmap (+1) pindex where
      pindex = C.elemIndexEnd ' ' headerText
    byteNumberStr = fmap B.drop vindex <*> pure headerText

parseRequestURI::B.ByteString -> [String]
parseRequestURI message = map C.unpack $ C.split '/' uriText
  where
    (_,uriStart) = B.breakSubstring (C.pack "/") message
    --drop starting / in URI
    (uriText, _) = B.breakSubstring (C.pack " ") (B.drop 1 uriStart)
    
parseRequestMethod::B.ByteString -> Maybe Method
parseRequestMethod message = case getMethod message of
  "GET" -> Just GET
  "POST" -> Just POST
  "DELETE" -> Just DELETE
  _ -> Nothing
  where  getMethod = C.unpack . fst . B.breakSubstring (C.pack " ")

serve::State->Handle->IO()
serve state hdl = do
  request <- C.hGetSome hdl 4096
  let contentLength = findContentLength request

  case parseRequestMethod request of
    Just method -> indexRoutes state contentLength method uri hdl
      where uri = parseRequestURI request   
    _ -> badRequestPage hdl

  
acceptLoop::State->Socket->IO ()
acceptLoop state serverSocket = do
  (client, _, _) <- accept serverSocket
  forkIO $ serve state client
  acceptLoop state serverSocket

main = do
  state <- newEmptyMVar
  putMVar state (0,[Driver 0 "Kyle" "now" 54 42 43])
  
  print $ findContentLength (C.pack"hello!\r\nwe\r\nContent-Length: 4233\r\nds\r\n")
  serverSocket <- listenOn (PortNumber 8080)
  acceptLoop state serverSocket
