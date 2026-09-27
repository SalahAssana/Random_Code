def load_data(filename):
    # Load movie ratings from file into a dictionary
    movie_ratings = {}
    with open(filename, 'r') as f:
        for line in f:
            user_id, movie_title, rating = line.strip().split(',')
            if user_id not in movie_ratings:
                movie_ratings[user_id] = {}
            movie_ratings[user_id][movie_title] = int(rating)
    return movie_ratings

def calculate_similarity(user1_ratings, user2_ratings):
    # Calculate the similarity between two users using cosine similarity
    intersection = set(user1_ratings.keys()) & set(user2_ratings.keys())
    dot_product = sum([user1_ratings[movie] * user2_ratings[movie] for movie in intersection])
    magnitude_user1 = (sum([rating ** 2 for rating in user1_ratings.values()])) ** 0.5
    magnitude_user2 = (sum([rating ** 2 for rating in user2_ratings.values()])) ** 0.5
    similarity = dot_product / (magnitude_user1 * magnitude_user2)
    return similarity

def recommend_movies(user_id, movie_ratings, user_similarities):
    # Recommend movies to a user based on the similarities with other users
    recommended_movies = []
    for similar_user in sorted(user_similarities, key=lambda x: user_similarities[x], reverse=True):
        if similar_user != user_id:
            for movie in set(movie_ratings[similar_user].keys()) - set(recommended_movies):
                if movie not in movie_ratings.get(user_id, {}):
                    recommended_movies.append(movie)
    return recommended_movies

def main():
    # Load the movie ratings data
    movie_ratings = load_data('movie_ratings.csv')

    # Calculate the similarities between users
    user_similarities = {}
    for user1 in movie_ratings:
        for user2 in movie_ratings:
            if user1 != user2 and user1 not in user_similarities:
                similarity = calculate_similarity(movie_ratings[user1], movie_ratings[user2])
                user_similarities[user1] = {user2: similarity}

    # Recommend movies to a user
    user_id = 'user1'
    recommended_movies = recommend_movies(user_id, movie_ratings, user_similarities.get(user_id, {}))

    print("Recommended movies for", user_id, ":", recommended_movies)

if __name__ == '__main__':
    main()