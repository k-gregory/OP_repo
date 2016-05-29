module Main where

import Driver
import HttpHelpers
import Text.JSON
import Text.Read
import Network
import System.IO
import System.Directory
import Control.Monad(liftM)
import Control.Concurrent(forkIO)
import Control.Concurrent.MVar
import qualified Data.ByteString.Char8 as C
import Data.List

class DriverRepository t where
  list::t->IO [Driver]
  findById::t->Int->IO (Maybe Driver)
  deleteById::t->Int->IO ()
  add::t->Driver->IO()

data MemDrivers = MemDrivers {
  elements:: MVar[Driver]
                             }

instance DriverRepository MemDrivers where
  list = readMVar . elements
  
  findById r sid = do
    drivers <- list r
    case filter (\d->index d == sid) drivers of
      [drv] -> return $ Just drv
      _ -> return Nothing
      
  deleteById r sid = do
    drivers <- takeMVar $ elements r
    let updated = filter (\d->index d /= sid) drivers
      in putMVar (elements r) updated
      
  add r newDriver = do
    oldDrivers <- takeMVar $ elements r
    let lastId = index $ last oldDrivers
        updateDriver d new_index = d { index = new_index}
        newDrivers = oldDrivers ++ [updateDriver newDriver (lastId+1)]
      in putMVar (elements r) newDrivers

allDriversPage repo hdl = do
  drivers <- list repo
  sendJSON hdl $ encode drivers
  hClose hdl


singleDriverPage driver hdl = do
  sendJSON hdl $ encode driver
  hClose hdl

addDriver req repo hdl = do
  putStrLn $ parseRequestBody req
  case (decode $ parseRequestBody req) of
    Ok drv -> add repo drv
    _ -> badRequestPage hdl

tryGetDriverOrBadRequest cb _id repo hdl = do
  let wantedId = readMaybe _id :: Maybe Int
    in  case wantedId of
          Nothing -> badRequestPage hdl
          Just sid -> do
            _driver <- findById repo sid
            case _driver of
              Just driver -> cb driver hdl
              Nothing -> pageNotFound hdl

testPage hdl = do
  C.hPutStr hdl $ createResponse "HTTP/1.1 200 OK" [ctJSONutf8] "Пиздос"
    
route staticServer request repo method uri hdl = do
  print(method, uri)
  case (method, uri) of
    (GET, []) -> staticServer "index.html" hdl
    (GET, ["test"]) -> testPage hdl
    (GET, ("static":other)) -> staticServer (intercalate "/" other) hdl
    (GET, ["api","drivers"]) ->  allDriversPage repo hdl
    (GET, ["api","drivers",_id]) ->
      tryGetDriverOrBadRequest singleDriverPage _id repo hdl
    (DELETE, ["api", "drivers", _id]) -> do
      case readMaybe _id ::Maybe Int of
        Just sid -> deleteById repo sid
        Nothing -> pageNotFound hdl
      hClose hdl

    (POST, ["api", "drivers"]) -> do
      addDriver request repo hdl
    _ -> pageNotFound hdl      
         
serve hdl repo staticServer = do
  request <- C.hGetSome hdl 4096
  case parseRequestMethod request of
    Just method -> route staticServer request repo method uri hdl
      where uri = parseRequestURI request
    _ -> badRequestPage hdl

acceptLoop serverSocket repo staticServer = do
  (client, _, _) <- accept serverSocket
  forkIO $ serve client repo staticServer
  acceptLoop serverSocket repo staticServer

main = do
  drvHolder <- newMVar [Driver 0 "UTF-8 Dead Moroze ЪЪЇЇ" "Новий рік" 0 0 0]
  servePath <- getCurrentDirectory
  staticServer <- createStaticServer $ servePath ++ "/static"
  serverSocket <- listenOn (PortNumber 8080)
  acceptLoop serverSocket (MemDrivers {elements = drvHolder}) staticServer
