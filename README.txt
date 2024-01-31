ReadMe
Introduction
This repository contains Python code for implementing k-NN classification, generating synthetic data for classification, and using a Random Forest Classifier on a real-world dataset. Additionally, the code includes a profiling function to measure the performance of the k-NN classification.

Files
1. knn_classification.py
Contains functions for k-NN classification, synthetic data generation, and Random Forest Classifier on a real-world dataset.
2. winequality-white-Train.csv and winequality-white-Test.csv
Sample datasets for the k-NN classification.
3. weatherAUS.csv
Real-world dataset for the Random Forest Classifier.
4. profile_code()
Function to profile the performance of the k-NN classification using the cProfile module.
5. requirements.txt
Lists the required Python packages. Install them using pip install -r requirements.txt.

Installation

1.Navigate to the project folder:
cd HPC

2.Install the required packages:
pip install -r requirements.txt


USAGE

1.Run the k-NN classification and synthetic data generation:
python 2.ipynb

2.To profile the performance of the k-NN classification, run:
python -m cProfile -o profile_output.prof knn_classification.py

Important Notes
Make sure to have Python installed (version 3.x recommended).

Verify that the required packages are installed by using the requirements.txt file.

Adjust file paths and names as needed.