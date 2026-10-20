#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <sqlite3.h>

// Define data structures
typedef struct {
    char title[256];
    char description[1024];
    char url[256];
} Website;

typedef struct {
    int id;
    char url[256];
    char crawled_at[64];
} CrawlLog;

// Function to crawl a website and extract information
void crawl_website(Website* website, sqlite3* db) {
    CURL *curl;
    CURLcode res;
    FILE *fp;
    char url[1024];

    // Set up curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        // Set the URL and user agent for curl
        strcpy(url, "http://example.com");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "C Web Crawler");

        // Perform the curl operation
        res = curl_easy_perform(NULL);

        // Check if there were any errors
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", 
                    curl_easy_strerror(res));
        }

        // Close the curl session
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    // Extract information from website and store in database
    sqlite3_stmt *stmt;
    const char* query = "INSERT INTO websites (title, description, url) VALUES (?, ?, ?)";
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if(rc == SQLITE_OK) {
        // Extract title and description from website
        FILE *fp = fopen("index.html", "r");
        char buffer[1024];
        while(fgets(buffer, sizeof(buffer), fp)) {
            // Check for title
            if(strstr(buffer, "<title>") != NULL) {
                strcpy(website->title, buffer);
                break;
            }
        }

        // Extract description from website
        fp = fopen("index.html", "r");
        while(fgets(buffer, sizeof(buffer), fp)) {
            // Check for description
            if(strstr(buffer, "<meta name=\"description\" content=\"") != NULL) {
                strcpy(website->description, buffer);
                break;
            }
        }

        // Store website information in database
        sqlite3_bind_text(stmt, 1, website->title, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, website->description, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, website->url, -1, SQLITE_STATIC);
        rc = sqlite3_step(stmt);
        if(rc == SQLITE_DONE) {
            printf("Website information stored in database.\n");
        } else {
            fprintf(stderr, "Error storing website information: %s\n", 
                    sqlite3_errmsg(db));
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
}

// Function to log crawl activity
void log_crawl(CrawlLog* log) {
    CURL *curl;
    CURLcode res;

    // Set up curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        // Set the URL and user agent for curl
        strcpy(url, "http://example.com");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "C Web Crawler");

        // Perform the curl operation
        res = curl_easy_perform(NULL);

        // Check if there were any errors
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", 
                    curl_easy_strerror(res));
        }

        // Close the curl session
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    // Store log in database
    sqlite3_stmt *stmt;
    const char* query = "INSERT INTO crawl_logs (id, url, crawled_at) VALUES (?, ?, ?)";
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if(rc == SQLITE_OK) {
        // Store log in database
        sqlite3_bind_int(stmt, 1, log->id);
        sqlite3_bind_text(stmt, 2, log->url, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, log->crawled_at, -1, SQLITE_STATIC);
        rc = sqlite3_step(stmt);
        if(rc == SQLITE_DONE) {
            printf("Crawl log stored in database.\n");
        } else {
            fprintf(stderr, "Error storing crawl log: %s\n", 
                    sqlite3_errmsg(db));
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
}

// Main function
int main() {
    sqlite3 *db;
    int rc;

    // Open the database
    rc = sqlite3_open("webcrawler.db", &db);
    if(rc) {
        fprintf(stderr, "Cannot open database: %s\n", 
                sqlite3_errmsg(db));
        return 1;
    }

    // Create tables in database
    const char* query = "CREATE TABLE IF NOT EXISTS websites (id INTEGER PRIMARY KEY, title TEXT, description TEXT, url TEXT)";
    rc = sqlite3_exec(db, query, NULL, NULL, NULL);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char* query2 = "CREATE TABLE IF NOT EXISTS crawl_logs (id INTEGER PRIMARY KEY, url TEXT, crawled_at TEXT)";
    rc = sqlite3_exec(db, query2, NULL, NULL, NULL);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Crawl websites and log activity
    Website website;
    crawl_website(&website, db);

    CrawlLog log;
    log.id = 1;
    strcpy(log.url, "http://example.com");
    strcpy(log.crawled_at, "2022-01-01");
    log_crawl(&log);

    // Close the database
    sqlite3_close(db);
    return 0;
}