{-
-- EPITECH PROJECT, 2024
-- main
-- File description:
-- for imagecompressor
-}

module Main (main) where
import System.Environment
import System.Exit
import ParsingAlgo

main :: IO ()
main = do
    args <- getArgs
    case getOpts defaultFlags args of                                                                           
        Just flags -> checkParams flags
        Nothing -> putStrLn "error: invalid arguments given"
                    >> exitWith (ExitFailure 84)
