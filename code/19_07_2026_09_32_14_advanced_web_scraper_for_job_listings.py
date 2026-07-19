import requests
from bs4 import BeautifulSoup
import sqlite3
from typing import List, Dict
from urllib.parse import urlparse, parse_qs

class JobListing:
    def __init__(self, title: str, company: str, location: str, url: str):
        self.title = title
        self.company = company
        self.location = location
        self.url = url

class Scraper:
    def __init__(self):
        self.url = "https://www.example.com/jobs"
        self.conn = sqlite3.connect("jobs.db")
        self.cursor = self.conn.cursor()

    def scrape(self) -> List[JobListing]:
        response = requests.get(self.url)
        soup = BeautifulSoup(response.text, "html.parser")

        jobs: List[JobListing] = []
        for job in soup.find_all("div", {"class": "job"}):
            title = job.find("h2").text.strip()
            company = job.find("span", {"class": "company"}).text.strip()
            location = job.find("span", {"class": "location"}).text.strip()
            url = urlparse(job.find("a")["href"]).geturl()
            jobs.append(JobListing(title, company, location, url))

        return jobs

    def store(self, jobs: List[JobListing]):
        for job in jobs:
            self.cursor.execute("INSERT INTO jobs (title, company, location, url) VALUES (?, ?, ?, ?)",
                                 (job.title, job.company, job.location, job.url))
        self.conn.commit()

if __name__ == '__main__':
    scraper = Scraper()
    jobs = scraper.scrape()
    scraper.store(jobs)