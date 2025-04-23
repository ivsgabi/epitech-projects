{-
-- EPITECH PROJECT, 2024
-- Parsing
-- File description:
-- for imagecompressor
-}

module ParsingAlgo (getOpts, defaultFlags, checkParams, parseFile, kmeansLoop) where
import Data.List (sortOn)
import System.Exit
import Text.Read
import Data.Maybe()
import System.Random

data Flags = Flags { nbColors :: Maybe Int, convLimit :: Maybe Float, filePath :: Maybe String } deriving (Show)

type Position = (Int, Int)
type Color = (Int, Int, Int)
type Pixel = (Position, Color)
type Pixels = [Pixel]
type Centroids = [Color]
type Cluster = (Color, Pixels)

defaultFlags :: Flags
defaultFlags = Flags { nbColors = Nothing, convLimit = Nothing,
                filePath = Nothing }

getOpts :: Flags -> [String] -> Maybe Flags
getOpts flags [] = Just flags
getOpts flags ("-n":value:rest) = 
    getOpts (flags { nbColors = readMaybe value }) rest
getOpts flags ("-l":value:rest) = 
    getOpts (flags { convLimit = readMaybe value }) rest
getOpts flags ("-f":value:rest) = 
    getOpts (flags { filePath = Just value }) rest
getOpts _ _ = Nothing

checkParams :: Flags -> IO ()
checkParams flags | nbColors flags == Nothing || convLimit flags == Nothing 
                    || filePath flags == Nothing =
        putStrLn "error: invalid arguments given" >> exitWith (ExitFailure 84)
    | otherwise = parseFile flags

getMaybePos :: String -> Maybe Position
getMaybePos str = case readMaybe str of
    Just (x,y) -> Just (x,y)
    Nothing -> Nothing
    
getMaybeColor :: String -> Maybe Color
getMaybeColor str = case readMaybe str of
    Just (r,g,b) -> Just (r,g,b)
    Nothing -> Nothing

getPixels :: [String] -> Pixels
getPixels [] = []
getPixels [[]] = []
getPixels [(_:_)] = []
getPixels (pos:color:rest) =
    case (getMaybePos pos, getMaybeColor color) of
        (Just p, Just c) -> (p, c) : getPixels rest
        _ -> getPixels rest

parseFile :: Flags -> IO ()
parseFile flags =
    case filePath flags of
        Just path -> do
            contents <- readFile path
            let wordsContent = words contents
                pixels = getPixels wordsContent
            kmeansInit flags pixels
        Nothing -> putStrLn "error: can not open the given file" 
                    >> exitWith (ExitFailure 84)

getFirstCentroids :: Flags -> Pixels -> StdGen -> Pixels
getFirstCentroids flags pixels gen = case nbColors flags of
    Just colorsnb -> take colorsnb (mixPixels gen pixels)
    Nothing -> []

mixPixels :: StdGen -> [a] -> [a]
mixPixels gen xs = map fst (sortOn snd (zip xs randomIndex))
    where randomIndex = randomRs (0, length xs - 1) gen

computeDistance :: Int -> Int -> Int -> Int -> Int -> Int -> Int
computeDistance x1 y1 x2 y2 x3 y3 = ((x1 - y1) * (x1 - y1)) + 
                                    ((x2 - y2) * (x2 - y2)) + 
                                    ((x3 - y3) * (x3 - y3))
                                    
squareRoot :: Int -> Float
squareRoot x = sqrt (fromIntegral x)

distance :: Color -> Color -> Float
distance (x1, x2, x3) (y1, y2, y3) = 
        squareRoot (computeDistance x1 y1 x2 y2 x3 y3)

getAllDistances :: Centroids -> Pixels -> [[Float]]
getAllDistances centroids pixels =
    map (\pixel -> map (\centroid -> distance pixel centroid) centroids)
    (extractOnlyColors pixels)

findIndexDistanceLoop :: [Float] -> Float -> Int -> Int -> Int
findIndexDistanceLoop (dist : rest) minim index result_index = if dist > minim
    then findIndexDistanceLoop rest minim (index + 1) result_index
    else findIndexDistanceLoop rest dist (index + 1) index
findIndexDistanceLoop [] _ _ result_index = result_index

findIndexDistance :: [Float] -> Int
findIndexDistance distances = 
    findIndexDistanceLoop distances (head distances) 0 0

getIndexCentroids :: [[Float]] -> [Int]
getIndexCentroids (dist : rest) = 
    findIndexDistance dist : getIndexCentroids rest
getIndexCentroids [] = []

loadCluster :: Cluster ->  Pixels -> Int -> [Int] -> Cluster
loadCluster (centroid, cluster_pixels) (pixel : rest)
    index (val : res_val) = if val == index
    then loadCluster (centroid, cluster_pixels ++ [pixel]) rest index res_val
    else loadCluster (centroid, cluster_pixels) rest index res_val
loadCluster cluster [] _ _ = cluster
loadCluster cluster _ _ [] = cluster

setClusterLoop :: Centroids -> Pixels -> [Int] -> Int -> [Cluster]
setClusterLoop (centroid : rest) pixels indexes index = 
    (loadCluster (centroid, []) pixels index indexes) : 
    setClusterLoop rest pixels indexes (index + 1)
setClusterLoop [] _ _ _ = []
    
setCluster :: Centroids -> Pixels -> [Int] -> [Cluster]
setCluster centroids pixels indexes = setClusterLoop centroids pixels indexes 0

getAllCluster :: Centroids -> Pixels -> [Cluster]
getAllCluster centroids pixels = setCluster centroids pixels 
    (getIndexCentroids (getAllDistances centroids pixels))

extractOnlyColors :: Pixels -> Centroids
extractOnlyColors pixels = map snd pixels

getMeansR :: Cluster -> Int
getMeansR (_, pixels) = round (fromIntegral (sumRed pixels) / 
    fromIntegral (length pixels) :: Double)

sumRed :: Pixels -> Int
sumRed = sum . map getRedComponent

getRedComponent :: Pixel -> Int
getRedComponent ((_, _), (redInt, _, _)) = redInt

getMeansG :: Cluster -> Int
getMeansG (_, pixels) = round (fromIntegral (sumGreen pixels) / 
    fromIntegral (length pixels) :: Double)

sumGreen :: Pixels -> Int
sumGreen = sum . map getGreenComponent

getGreenComponent :: Pixel -> Int
getGreenComponent ((_, _), (_, greenInt, _)) = greenInt

getMeansB :: Cluster -> Int
getMeansB (_, pixels) = round (fromIntegral (sumBlue pixels) / 
    fromIntegral (length pixels) :: Double)

sumBlue :: Pixels -> Int
sumBlue = sum . map getBlueComponent

getBlueComponent :: Pixel -> Int
getBlueComponent ((_, _), (_, _, blueInt)) = blueInt

updateCentroids :: [Cluster] -> Centroids
updateCentroids clusteredPixels = map (\cluster -> (getMeansR cluster, 
    getMeansG cluster, getMeansB cluster)) clusteredPixels

getCentroidDistance :: Centroids -> Centroids -> Float
getCentroidDistance [] [] = 0
getCentroidDistance (c1:cs1) (c2:cs2) = 
    distance c1 c2 + getCentroidDistance cs1 cs2
getCentroidDistance _ _ = 84

-- displayClusters :: [Cluster] -> IO ()
-- displayClusters [] = putStrLn ""
-- displayClusters ((centroid, clusterPixels):rest) =
--     putStrLn ("--\n" ++ show centroid ++ "\n-") >>
--     displayClusterPixels clusterPixels >>
--     displayClusters rest

displayClusters :: [Cluster] -> IO ()
displayClusters [] = putStrLn ""
displayClusters [(centroid, clusterPixels)] =
    putStrLn ("--\n" ++ show centroid ++ "\n-") >>
    displayClusterPixels clusterPixels
displayClusters ((centroid, clusterPixels):rest) =
    putStrLn ("--\n" ++ show centroid ++ "\n-") >>
    displayClusterPixels clusterPixels >>
    displayClusters rest

displayClusterPixels :: Pixels -> IO ()
displayClusterPixels clusterPixels =
    mapM_ (\(position, color) -> putStrLn 
    (show position ++ " " ++ show color)) clusterPixels

kmeansInit :: Flags -> Pixels -> IO ()
kmeansInit flags pixels = do
            gen <- newStdGen
            let centroids = getFirstCentroids flags pixels gen
            kmeansLoop (extractOnlyColors centroids) pixels flags

kmeansLoop :: Centroids -> Pixels -> Flags -> IO ()
kmeansLoop centroids allPixels flags =
    if convLimit flags < Just centroidDistance
        then kmeansLoop newCentroids allPixels flags
        else displayClusters clusteredPixels
    where
        clusteredPixels = getAllCluster centroids allPixels
        newCentroids = updateCentroids clusteredPixels
        centroidDistance = getCentroidDistance centroids newCentroids
