import queue
from bs4 import BeautifulSoup
from urllib.parse import urlparse, urljoin
import requests
import re

class Page:
    def __init__(self, url):
        self.url = url
        self.importance = 0
        self.content = None

    def set_importance(self, importance):
        self.importance = importance

    def get_content(self):
        return self.content

class PriorityWebCrawler:
    def __init__(self, start_url, max_depth=2):
        self.start_url = start_url
        self.max_depth = max_depth
        self.crawled_pages = {}
        self.to_crawl = queue.PriorityQueue()

        self.to_crawl.put(Page(self.start_url), 0)

    def crawl(self):
        while not self.to_crawl.empty():
            page = self.to_crawl.get()
            if page.url in self.crawled_pages:
                continue

            self.crawled_pages[page.url] = True
            print(f"Crawling {page.url}...")

            try:
                response = requests.get(page.url)
                response.raise_for_status()

                soup = BeautifulSoup(response.text, 'html.parser')

                page.set_importance(self.calculate_importance(soup))
                page.set_content(soup.title.string)

                self.extract_links(soup, page)

            except Exception as e:
                print(f"Error crawling {page.url}: {e}")

    def extract_links(self, soup, page):
        for link in soup.find_all('a'):
            href = link.get('href')
            if not href:
                continue

            url = urlparse(href).geturl()
            if re.match(r'^https?://', url):
                self.to_crawl.put(Page(url), 0)

    def calculate_importance(self, soup):
        importance = 0
        for tag in ['h1', 'h2', 'h3']:
            tags = soup.find_all(tag)
            importance += len(tags) * (10 ** (4 - len(str(tags))))

        return importance

    def main(self):
        start_url = "https://example.com"
        crawler = PriorityWebCrawler(start_url, max_depth=1)

        crawler.crawl()

if __name__ == '__main__':
    WebCrawler.main()