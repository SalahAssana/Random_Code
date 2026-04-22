import numpy as np
from sklearn.metrics.pairwise import cosine_similarity
from scipy.sparse.linalg import svds

class Movie:
    def __init__(self, title, genre, rating):
        self.title = title
        self.genre = genre
        self.rating = rating

def load_movies(filename):
    movies = []
    with open(filename, 'r') as f:
        for line in f:
            title, genre, rating = line.strip().split(',')
            movie = Movie(title, genre, float(rating))
            movies.append(movie)
    return movies

def build_similarity_matrix(movies):
    # Convert ratings to binary (0/1) values
    ratings_binary = [[int(movie.rating >= 4)] for movie in movies]

    # Compute cosine similarity between each pair of movies
    similarities = cosine_similarity(np.array(ratings_binary))

    return similarities

def recommend_movies(user_ratings, movies, num_recommendations):
    # Convert user ratings to binary (0/1) values
    user_ratings_binary = [int(rating >= 4) for rating in user_ratings]

    # Compute similarity between the user and each movie
    user_similarities = np.dot(user_ratings_binary, movies)

    # Sort movies by similarity and select top N recommendations
    indices = np.argsort(-user_similarities)[:num_recommendations]
    recommended_movies = [movies[i] for i in indices]

    return recommended_movies

# Load synthetic movie data (replace with real data)
movies = load_movies('movies.txt')

# Compute similarity matrix between movies
similarity_matrix = build_similarity_matrix(movies)

# Perform SVD decomposition to reduce dimensionality
U, sigma, Vt = svds(similarity_matrix, k=5)

# Convert ratings from binary values to original rating scale (0-5)
ratings = [movie.rating for movie in movies]

# Make predictions using collaborative filtering
predictions = np.dot(U * sigma, Vt.T)

if __name__ == '__main__':
    # Define a sample user with some ratings
    user_ratings = [4.0, 3.5, 2.0, 4.5, 1.0]

    # Recommend movies based on the user's ratings and genres
    recommended_movies = recommend_movies(user_ratings, movies, 5)

    print("Recommended Movies:")
    for movie in recommended_movies:
        print(f"{movie.title} ({movie.genre})")