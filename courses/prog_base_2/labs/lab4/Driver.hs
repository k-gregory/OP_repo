module Driver where

import Text.JSON
import Control.Monad(mzero)

data Driver = Driver {
  index :: Int,
  name :: String,
  workStartDate :: String,
  satisfiedClients :: Int,
  averageSpeed :: Double,
  kmFare :: Double
  } deriving(Show)

instance JSON Driver where
  showJSON d =
    makeObj [
    put "name" name,
    put "workStartDate" workStartDate,
    put "satisfiedClients" satisfiedClients,
    put "averageSpeed" averageSpeed,
    put "kmFare" kmFare]
    where put prop propName = (prop, showJSON $ propName d)
  readJSON (JSObject obj) =
    Driver 0 <$>
    get "name" <*>
    get "workStartDate" <*>
    get "satisfiedClients" <*>
    get "averageSpeed" <*>
    get "kmFare"
    where get fieldName = valFromObj fieldName obj
  readJSON _ = mzero
