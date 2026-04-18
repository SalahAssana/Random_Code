# Import necessary libraries
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
from sklearn.ensemble import RandomForestClassifier
from joblib import dump, load
import os

# Load data
train_df = pd.read_csv('train.csv')
test_df = pd.read_csv('test.csv')

# Split data into training and validation sets
X_train, X_val, y_train, y_val = train_test_split(train_df.drop('target', axis=1), 
                                                  train_df['target'], 
                                                  test_size=0.2, 
                                                  random_state=42)

# Scale features using StandardScaler
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_val_scaled = scaler.transform(X_val)
test_df_scaled = scaler.transform(test_df)

# Train a Random Forest classifier
rf_model = RandomForestClassifier(n_estimators=100, 
                                  random_state=42, 
                                  max_depth=5)
rf_model.fit(X_train_scaled, y_train)

# Evaluate model on validation set
y_pred = rf_model.predict(X_val_scaled)
print("Validation Accuracy:", accuracy_score(y_val, y_pred))
print("Classification Report:")
print(classification_report(y_val, y_pred))
print("Confusion Matrix:")
print(confusion_matrix(y_val, y_pred))

# Save trained model to disk
dump(rf_model, 'rf_model.joblib')

# Load saved model for inference
loaded_rf_model = load('rf_model.joblib')

# Make predictions on test set
y_pred_test = loaded_rf_model.predict(test_df_scaled)

# Save predicted probabilities to file
np.savetxt('predictions.csv', y_pred_test)