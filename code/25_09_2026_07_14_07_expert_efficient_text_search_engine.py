#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import re
from collections import defaultdict
import heapq
import os

class TextSearchEngine:
    def __init__(self):
        self.index = defaultdict(dict)

    def build_index(self, path):
        """
        Build an inverted index from the given text files.
        
        :param path: The directory containing the text files.
        :return: None
        """
        for filename in os.listdir(path):
            if filename.endswith(".txt"):
                with open(os.path.join(path, filename), "r") as file:
                    text = file.read()
                    words = re.findall(r'\b\w+\b', text.lower())
                    word_counts = defaultdict(int)
                    for word in words:
                        word_counts[word] += 1
                    for word, count in word_counts.items():
                        if count > 0:
                            self.index[filename][word] = count

    def search(self, query):
        """
        Search the index for matching documents.
        
        :param query: The search query (e.g., "hello world").
        :return: A list of tuples containing the document name and relevance score for each match.
        """
        results = []
        words = re.findall(r'\b\w+\b', query.lower())
        for filename, word_counts in self.index.items():
            if all(word in word_counts and word_counts[word] > 0 for word in words):
                relevance_score = sum(min(count, 1) for word, count in word_counts.items() if word in words)
                results.append((filename, relevance_score))
        return results

    def rank_results(self, results):
        """
        Rank the search results by relevance score.
        
        :param results: The list of search results.
        :return: A ranked list of tuples containing the document name and relevance score for each match.
        """
        return heapq.nlargest(len(results), results, key=lambda x: x[1])

    def run(self):
        if __name__ == '__main__':
            engine = TextSearchEngine()
            engine.build_index("path/to/text/files")
            query = "search query"
            results = self.search(query)
            ranked_results = self.rank_results(results)
            for result in ranked_results:
                print(f"Document: {result[0]}, Relevance Score: {result[1]}")

if __name__ == '__main__':
    TextSearchEngine().run()