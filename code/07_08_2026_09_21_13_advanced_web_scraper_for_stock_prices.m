% Web Scraper for Stock Prices
% ADVANCED complexity project

% Import necessary libraries
import org.jsoup.Jsoup;
import java.io.IOException;

% Function to scrape stock prices from website
function scrapeStockPrices()
    % URL of the website to scrape
    url = 'https://www.example.com/stockprices';
    
    % Connect to the website and get HTML content
    doc = Jsoup.connect(url).get();
    
    % Find all table rows in the HTML content
    tableRows = doc.select('table tr');
    
    % Initialize an empty matrix to store stock prices
    stockPrices = [];
    
    % Loop through each table row
    for i = 1:size(tableRows, 2)
        % Get the table data (td) elements
        tableData = tableRows{i}.select('td');
        
        % Extract the stock symbol and price from each table data element
        stockSymbol = tableData{1}.text();
        stockPrice = str2double(tableData{2}.text());
        
        % Append the stock symbol and price to the matrix
        stockPrices = [stockPrices; stockSymbol, stockPrice];
    end
    
    % Display the stock prices in a table
    disp(cell2mat(stockPrices));
end

% Main function to test the scrapeStockPrices function
function main()
    % Call the scrapeStockPrices function
    scrapeStockPrices();
    
    % Wait for user input before terminating the program
    pause;
end
