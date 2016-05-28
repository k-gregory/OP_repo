module Main where

import Driver
import HttpHelpers
import Text.JSON
import Text.Read
import Network
import System.IO
import Control.Monad(liftM)
import Control.Concurrent(forkIO)
import Control.Concurrent.MVar
import qualified Data.ByteString.Char8 as C

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


badRequestPage::Handle->IO ()
badRequestPage hdl = do
    hPutStr hdl "HTTP/1.1 400 Bad Request\r\n\
                \Content-Length: 10\r\n\
                \\r\n\
                \Bad request"
    hClose hdl

pageNotFound hdl = do
    hPutStr hdl "HTTP/1.1 404 Page Not Found\n\
                \Content-Length: 4\r\n\
                \\r\n\
                \404!"
    hClose hdl    

indexPage::Handle->IO ()
indexPage hdl = do
    hPutStr hdl "HTTP/1.1 200 OK\r\n\
                \Content-Length: 10\r\n\
                \\r\n\
                \Index page"
    hClose hdl

allDriversPage repo hdl = do
  drivers <- list repo
  hPutStr hdl $ encode drivers
  hClose hdl


singleDriverPage driver hdl = do
  hPutStr hdl $ encode driver
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
              _ -> badRequestPage hdl
              
    
route request repo method uri hdl = do
  print( method, uri)
  case (method, uri) of
    (GET, [""]) -> indexPage hdl
    (GET, ["api","drivers"]) ->  allDriversPage repo hdl
    (GET, ["api","drivers",_id]) ->
      tryGetDriverOrBadRequest singleDriverPage _id repo hdl
    (DELETE, ["api", "drivers", _id]) -> do
      case readMaybe _id ::Maybe Int of
        Just sid -> deleteById repo sid
      hClose hdl

    (POST, ["api", "drivers"]) -> do
      addDriver request repo hdl
    _ -> pageNotFound hdl      
         
serve hdl repo = do
  request <- C.hGetSome hdl 4096
  case parseRequestMethod request of
    Just method -> route request repo method uri hdl
      where uri = parseRequestURI request
    _ -> badRequestPage hdl


acceptLoop serverSocket repo = do
  (client, _, _) <- accept serverSocket
  forkIO $ serve client repo
  acceptLoop serverSocket repo

main = do
  drvHolder <- newMVar [(Driver 0 "Root" "19" 0 0 0)]
  serverSocket <- listenOn (PortNumber 8080)
  acceptLoop serverSocket (MemDrivers {elements = drvHolder})
