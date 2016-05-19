module Main where

import Network.Socket
import System.IO
import Control.Exception
import Control.Concurrent
import Control.Concurrent.Chan
import Control.Monad(liftM, when)
import Control.Monad.Fix(fix)

type Msg = (Int,String)

mainLoop::Socket->Chan Msg->Int->IO()
mainLoop sock chan msgNum = do
  conn <- accept sock
  forkIO (handleClient conn chan msgNum)
  mainLoop sock chan $! msgNum + 1

handleClient::(Socket, SockAddr)->Chan Msg->Int->IO()
handleClient (client,_) chan msgNum = do
  let broadcast msg = writeChan chan (msgNum, msg)
  
  hdl <- socketToHandle client ReadWriteMode
  hSetBuffering hdl NoBuffering

  hPutStrLn hdl "Hi, what's ur name ?"
  name <- liftM init (hGetLine hdl)

  broadcast ("-->" ++ name ++ " entered the chat!")
  hPutStrLn hdl ("Welcome, " ++ name ++ "!")
  
  commLine <- dupChan chan

  reader <- forkIO $ fix $ \loop -> do
    (nextNum,line) <- readChan commLine
    when (msgNum /= nextNum) $ hPutStrLn hdl line
    loop

  handle (\(SomeException _) -> return()) $ fix $ \loop -> do
    line <- liftM init (hGetLine hdl)
    case line of
      "quit" -> hPutStrLn hdl "Bye"
      _      -> broadcast (name ++ ": " ++ line) >> loop

  killThread reader
  broadcast("<--" ++ name ++ "left.")
  hClose hdl

main = do
  sock <- socket AF_INET Stream 0
  setSocketOption sock ReuseAddr 1

  chan <- newChan

  bind sock (SockAddrInet 8080 iNADDR_ANY)
  listen sock 2

  forkIO $ fix $ \loop -> do
    (_,msg) <- readChan chan
    loop

  mainLoop sock chan 0
