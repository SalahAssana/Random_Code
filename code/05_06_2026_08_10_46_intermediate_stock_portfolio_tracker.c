#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STOCKS 1000
#define MAX_DATE 20

typedef struct {
    char symbol[10];
    double initialInvestment;
    double currentPrice;
} Stock;

typedef struct {
    int date;
    double totalValue;
} PortfolioData;

Stock portfolio[MAX_STocks];
PortfolioData data[MAX_DATE];

void calculatePortfolioValues(int date) {
    double totalInitial = 0.0;
    double totalCurrent = 0.0;
    
    for (int i = 0; i < MAX_STOCKS; i++) {
        totalInitial += portfolio[i].initialInvestment;
        totalCurrent += portfolio[i].currentPrice * portfolio[i].initialInvestment;
    }
    
    data[date].totalValue = totalCurrent;
}

double calculateReturn(int date) {
    if (date == 0)
        return -1.0; // Error, no previous value available
    else
        return (data[date].totalValue / data[0].totalValue - 1.0);
}

void displayPortfolioValues() {
    printf("Stock\tInitial Investment\tCurrent Price\n");
    
    for (int i = 0; i < MAX_STOCKS; i++) {
        printf("%s\t%.2f\t%.2f\n", portfolio[i].symbol, portfolio[i].initialInvestment, portfolio[i].currentPrice);
    }
}

void displayPortfolioPerformance() {
    int date;
    double returnVal;
    
    printf("Date\tTotal Value\n");
    
    for (date = 0; date < MAX_DATE; date++) {
        printf("%d\t%.2f\n", date, data[date].totalValue);
    }
    
    printf("\nReturn (%.2f%%)\n", calculateReturn(MAX_DATE) * 100.0);
}

int main() {
    // Synthetic data
    strcpy(portfolio[0].symbol, "AAPL");
    portfolio[0].initialInvestment = 100.0;
    portfolio[0].currentPrice = 150.0;
    
    strcpy(portfolio[1].symbol, "MSFT");
    portfolio[1].initialInvestment = 50.0;
    portfolio[1].currentPrice = 120.0;
    
    calculatePortfolioValues(0);
    data[0].totalValue = portfolio[0].initialInvestment + portfolio[1].initialInvestment;
    
    for (int i = 1; i < MAX_DATE; i++) {
        calculatePortfolioValues(i);
        data[i].totalValue += (portfolio[0].currentPrice - portfolio[0].currentPrice) * portfolio[0].initialInvestment
                              + (portfolio[1].currentPrice - portfolio[1].currentPrice) * portfolio[1].initialInvestment;
    }
    
    displayPortfolioValues();
    displayPortfolioPerformance();
    
    return 0;
}