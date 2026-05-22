import requests
from bs4 import BeautifulSoup
from collections import deque
from urllib.parse import urljoin, urlparse

class JobScraper:
    def __init__(self):
        self.visited = set()
        self.queue = deque()

    def is_valid(self, url):
        return (url.startswith('https://') or url.startswith('http://')) and urlparse(url).netloc in ['www.linkedin.com', 'www.glassdoor.com']

    def get_linked_pages(self, soup):
        links = []
        for link in soup.find_all('a'):
            href = link.get('href')
            if href:
                absolute_url = urljoin(link.attrs['href'], '')
                parsed_link = urlparse(absolute_url)
                if self.is_valid(absolute_url) and parsed_link.netloc == urlparse(soup.url).netloc:
                    links.append((absolute_url, link.text))
        return links

    def scrape(self):
        soup = BeautifulSoup(requests.get('https://www.linkedin.com/jobs/').content, 'html.parser')
        for job in self.get_linked_pages(soup):
            if job[0] not in self.visited:
                self.queue.append(job)
                self.visited.add(job[0])
        while self.queue:
            url, title = self.queue.popleft()
            soup = BeautifulSoup(requests.get(url).content, 'html.parser')
            for link in self.get_linked_pages(soup):
                if link[0] not in self.visited and link[1].startswith(title):
                    self.queue.append(link)
                    self.visited.add(link[0])
        return [job[0] for job in self.queue]

if __name__ == '__main__':
    scraper = JobScraper()
    print(scraper.scrape())