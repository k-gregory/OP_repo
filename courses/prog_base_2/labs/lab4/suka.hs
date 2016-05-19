module Main where
 
import Network.Socket
import System.IO
import Control.Exception
import Control.Concurrent
import Control.Concurrent.Chan
import Control.Monad (liftM, when)
import Control.Monad.Fix (fix)
 
main :: IO ()
main = do
  sock <- socket AF_INET Stream 0
  setSocketOption sock ReuseAddr 1
  bind sock (SockAddrInet 4242 iNADDR_ANY)
  listen sock 2
  chan <- newChan
  forkIO $ fix $ \loop -> do
    (_, msg) <- readChan chan
    loop
  mainLoop sock chan 0
 
type Msg = (Int, String)
 
mainLoop :: Socket -> Chan Msg -> Int -> IO ()
mainLoop sock chan msgNum = do
  conn <- accept sock
  forkIO (runConn conn chan msgNum)
  mainLoop sock chan $! msgNum + 1
 
runConn :: (Socket, SockAddr) -> Chan Msg -> Int -> IO ()
runConn (sock, _) chan msgNum = do
    let broadcast msg = writeChan chan (msgNum, msg)
    hdl <- socketToHandle sock ReadWriteMode
    hSetBuffering hdl NoBuffering
 
    hPutStrLn hdl "Hi, what's your name?"
    name <- liftM init (hGetLine hdl)
    broadcast ("--> " ++ name ++ " entered chat.")
    hPutStrLn hdl ("Welcome, " ++ name ++ "!")
 
    commLine <- dupChan chan
 
    -- fork off a thread for reading from the duplicated channel
    reader <- forkIO $ fix $ \loop -> do
        (nextNum, line) <- readChan commLine
        when (msgNum /= nextNum) $ hPutStrLn hdl line
        loop
 
    handle (\(SomeException _) -> return ()) $ fix $ \loop -> do
        line <- liftM init (hGetLine hdl)
        case line of
             -- If an exception is caught, send a message and break the loop
             "quit" -> hPutStrLn hdl "Bye!"
             -- else, continue looping.
             _      -> broadcast (name ++ ": " ++ line) >> loop
 
    killThread reader                      -- kill after the loop ends
    broadcast ("<-- " ++ name ++ " left.") -- make a final broadcast
    hClose hdl
