% Stock Market Analysis
%
% Copyright 2023, Your Name/Your Organization (example)

% Import necessary libraries
import matlab.io.*;

% Define constants and variables
const stockNames = ["AAPL", "GOOG", "MSFT"];
const startDate = "2010-01-01";
const endDate = "2022-12-31";
const dataDir = "stock_data/"; % directory containing stock data files

% Function to load stock data from file
function [dates, prices] = loadStockData(stockName)
    filename = [dataDir, stockName, ".csv"];
    dates = csvread(filename, 1, 0);
    prices = csvread(filename, 2, 0);
end

% Function to calculate moving averages
function ma = calculateMA(prices, windowSize)
    ma = zeros(size(prices, 1), 1);
    for i = 1:windowSize:length(prices)
        ma(i) = mean(prices(i:i+windowSize-1));
    end
end

% Function to plot stock data and moving averages
function [] = plotStockData(stockName, dates, prices, ma)
    figure;
    subplot(2, 1, 1);
    plot(dates, prices);
    title([stockName, " Stock Price"]);
    subplot(2, 1, 2);
    plot(dates, ma);
    title([stockName, " Moving Average (", num2str(length(prices)), ")"]);
end

% Main script
if nargin == 0
    stockNames = ["AAPL", "GOOG", "MSFT"];
else
    stockNames = {nargin};
end

for i = 1:length(stockNames)
    [dates, prices] = loadStockData(stockNames{i});
    ma = calculateMA(prices, 50); % calculate moving average with window size 50
    plotStockData(stockNames{i}, dates, prices, ma);
end