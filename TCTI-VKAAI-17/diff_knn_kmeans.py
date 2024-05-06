# Python Modules
import random
# import matplotlib.pyplot as plt

# Project Modules
from Datasets.import_dataset import normalize_dataset, load_labelled_dataset

import KMEANS.KMEANS_jort_de_boer as kmeans
import KNN.KNN_jort_de_boer as knn


# skip K=0
TEST_UNTIL_K=range(1, 100)
VERBOSE=True

if __name__ == "__main__":
    
    # Set fixed seed to get xxx results.
    random.seed(0)
    
    # Load and normalize "test"-dataset
    test_labels, test_data = \
            normalize_dataset(
                    load_labelled_dataset("Datasets/dataset1.csv"), 
                    is_labelled=True)
            
    # Load and normalize "validation"-dataset
    val_labels, val_data = \
            normalize_dataset(
                    load_labelled_dataset("Datasets/validation1.csv"), 
                    is_labelled=True)
    
    
    # Run both algorithms for the value K in range of "TEST_UNTIL_K" and plot the results.
    kmeans_data_points = []
    knn_data_points = []
    for k in TEST_UNTIL_K:
        if VERBOSE:
            print(f"\nK: {k}")
        
        # KMeans
        centroids = kmeans.get_best_centroids(test_data, k)
        labeled_ctds = kmeans.classify(test_data, test_labels, centroids)
        accuracy = kmeans.get_accuracy(val_data, val_labels, labeled_ctds)
        kmeans_data_points.append( accuracy )
        if VERBOSE:
            print(f"KMEANS: with {accuracy}% ")
        
        # KNN
        accuracy = knn.get_accuracy(k, val_data, val_labels, test_data, test_labels)
        knn_data_points.append(accuracy)
        if VERBOSE: 
            print(f"KNN:  with {accuracy}%")
     
    # Plot the accuracies
    # plt.title('Accuracy Test')
    # plt.plot(TEST_UNTIL_K, knn_data_points, label='KNN Accuracy')
    # plt.plot(TEST_UNTIL_K, kmeans_data_points, label='KMeans Accuracy')
    # plt.legend()
    # plt.xlabel('K-value')
    # plt.ylabel('Accuracy')
    # plt.savefig('accuracy_diff.png')
    # plt.show()
    
    
 