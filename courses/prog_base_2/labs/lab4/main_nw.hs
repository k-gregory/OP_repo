module Main where

import Network.Socket
import System.IO
import Control.Exception
import Control.Concurrent
import Control.Concurrent.Chan
import Control.Monad(liftM)
import Control.Monad.Fix(fix)

type Msg = String

mainLoop::Socket->Chan Msg->IO()
mainLoop sock chan = do
  conn <- accept sock
  forkIO (handleClient conn chan)
  mainLoop sock chan

handleClient::(Socket, SockAddr) -> Chan Msg -> IO()
handleClient (client,_) chan = do
  let broadcast msg = writeChan chan msg
  
  hdl <- socketToHandle client ReadWriteMode
  hSetBuffering hdl NoBuffering
  commLine <- dupChan chan

  forkIO $ fix $ \loop -> do
    line <- readChan chan
    hPutStrLn hdl line
    loop

  fix $ \loop -> do
    line <- liftM  init (hGetLine hdl)
    broadcast line
    loop
  
  hPutStrLn hdl "Hello!"
  hClose hdl

main = do
  sock <- socket AF_INET Stream 0
  setSocketOption sock ReuseAddr 1

  chan <- newChan

  bind sock (SockAddrInet 8080 iNADDR_ANY)
  listen sock 2
  
  mainLoop sock chan
