# Python Modules
from collections import Counter
import numpy as np
import matplotlib.pyplot as plt
import random
import sys
sys.path.append('../')

# Project Modules
from Datasets.import_dataset import normalize_dataset, load_labelled_dataset

'''
====================================================================================
=                           K-Means Definitions                                    =
====================================================================================
'''
# Centroids:
#   [ <centroid>,
#     <centroid>
#     etc.
#   ]
#
# Cluster:
#   [ <centroid>, [<data_points>] ]
#
# Cluster_list:
#   [ [<centroid>, [<data_points>]]
#     [<centroid>, [<data_points>]]
#     etc.
#   ]
'''
====================================================================================
=                           K-Means functions                                      =
====================================================================================
'''
       
def get_random_centroids(test_data, n_centroids):
    '''
        Return a list with "randomly" chosen centroids.
        
        @param test_data        Dataset with data_points.
        @Param n_centroids      Amount of centroids.
        
        @Return                 Ndarray of "random" data_points (centroids); centroids.
    '''
    rand_ints = [random.randint(0, len(test_data)-1) for i in range(n_centroids)]
    return [test_data[rand_int] for rand_int in rand_ints]


def get_new_cluster_list(centroids):
    '''
        Return new list to store clusters.
        
        @param centroids        Centroids to store data for.
        
        @Return                 Ndarray of clusters; cluster_list
    '''
    return [[centroid, []] for centroid in centroids]


def get_centroids(test_data, centroids):
    '''
        Cluster data points to "their" closest centroids. 
            recursively re-cluster until the centroids are stable.
        
        @param test_data        Dataset with data_points
        @param centroids        Ndarray of centroids; centroids
        
        @Return                 Ndarray of clusters; cluster_list
    '''
    cluster_list = get_new_cluster_list(centroids)
    
    # Loop over all the data points to allocate them to their closest centroid.
    for data_point in test_data:
        distances = [ np.linalg.norm(centroid[0] - data_point) for centroid in cluster_list ]
        
        # Save the distances along with the actual data point, so we reduce the amount of "np.linalg.norm" calls.
        cluster_list[distances.index(min(distances))][1].append((data_point, pow(min(distances), 2)))

    
    new_centroids = adjust_centroids_to_mean(cluster_list)
    
    # If none of the centroids changed, we found the "optimal" mean.
    if np.array_equal(centroids, new_centroids, True):
        # Since the last clustering, the centroids did not change, so the data point will be the same.
        return cluster_list
    
    # Re-cluster recursively until the centroids don't change anymore.
    return get_centroids(test_data, new_centroids)


def adjust_centroids_to_mean(cluster_list):
    '''
        Adjust centroids to mean of clustered data.
        
        @param cluster_list	    Ndarray of clusters; cluster_list
        
        @Return                 Ndarray of centroids; centroids
    '''
    adjusted_centroids = []
    
    for cluster in cluster_list:
        
        # If there's no data point to adjust to, skip this calculation
        if not cluster[1]:
            adjusted_centroids.append(cluster[0])
            continue
                
        # calculate mean based on clustered data points; shape(7,)
        # We need *[0], because we store the Tuple: (data_point, eu-distances)
        adjusted_centroid =  np.mean(cluster[1], axis=0, dtype=object)[0]
        adjusted_centroids.append( adjusted_centroid )

    return adjusted_centroids

def classify(data, labels, centroids):
    '''
        Classify the given centroids.
        
        @param data	            Dataset with data_points
        @param labels           Ndarray with labels corresponding with the data(points)
        @param centroids        Ndarray of centroids; centroids
        
        @Return                 Ndarray of [ centroid, [label] ]
    '''
    cluster_list = get_new_cluster_list(centroids)
    
    for index, data_point in enumerate(data):
        # Get distance of the data_point to all the centroids
        distances = [np.linalg.norm(centroid - data_point) for centroid in centroids]

        # Add the datapoint to the list of the centroid with the smallest distance
        cluster_list[distances.index(min(distances))][1].append(labels[index])
    
    labels = []
    for cluster in cluster_list:
        # If a cluster doesnt have cluster data poitns, we cant label it
        # so add an empty labelled cluster to keep the shape intact
        if cluster[1]:
            labels.append((cluster[0] , Counter(cluster[1]).most_common()[0][0]))
        else:
            labels.append((cluster[0] , None ))
    return labels

'''
====================================================================================
=                          Setup and Stats                                         =
====================================================================================
'''
   
def get_best_centroids(test_data, k=4, n_iterations=10):
    '''
        Determine the "best" centroid by performing multiple iterations.
        
        @param test_data	    Dataset with data_points
        @param k                Amount of clusters
        @param n_iterations     Amount of iterations we will perform
        
        @Return                 Ndarray of centroids; centroids
    '''
    best_centroids = None
    
    # Perform K-means n_iterations times
    for i in range(n_iterations):
        
        # Get some random centroids to start with
        rand_centroids = get_random_centroids(test_data, k)
        
        # Ndarray of K times [centroid , (clustered data_points, eu-distances to centroid)]
        adjusted_centroids = get_centroids(test_data, rand_centroids)
        
        # transpose array so we can easily sum all the distances.
        transposed_centroids = np.transpose(adjusted_centroids)
        centroid = transposed_centroids[0], np.sum(transposed_centroids[1], axis=0)[1][1]
        
        # simple "get smallest distance"
        if best_centroids:
            if best_centroids[1] > centroid[1]:
                best_centroids = centroid
        else:
            best_centroids = centroid
            
    # Return just the "best" centroids out of all the n_iterations
    return best_centroids[0]


def get_accuracy(val_data, val_labels, labeled_ctds):
    '''
        Measure the accuracy of the labeled centroids.
        
        @param val_data	        Dataset with data_points
        @param val_labels       Ndarray with validated labels for data_points
        @param labeled_ctds     Ndarray of labeled centroids
        
        @Return                 
    '''
    correct = 0

    for index, val_point in enumerate(val_data):
        
        distances = [np.linalg.norm(centroid[0] - val_point) for centroid in labeled_ctds]
        closest_centroid = labeled_ctds[distances.index(min(distances))]
        
        correct += (closest_centroid[1] == val_labels[index])
        
    return (correct / len(val_data) * 100)

def create_screeplot(test_data, n_clusters):
    '''
        Create Screeplot.
        
        @param test_data        Dataset with data_points
        @param n_clusters       Amount of clusters to "plot/test"; Equivalent of K
        
        @Return                 
    '''
    testedKparams = range(1, n_clusters)
         
    # start at 0, end at -1. Keep the same shape as "testedKparams"
    screePlotPoints = np.zeros((n_clusters-1,))
    for k in testedKparams:

        centroids = get_best_centroids(test_data, k)
        
        cluster_list = get_new_cluster_list(centroids)
        # Loop over all the data points to allocate them to their closest centroid.
        for data_point in test_data:
            distances = [ np.linalg.norm(centroid[0] - data_point) for centroid in cluster_list ]
        
            cluster_list[distances.index(min(distances))][1].append(data_point)

        # Calculate the intra cluster distance
        # This is the distance between the centroid and all of its data_points
        for cluster in cluster_list:
            for cluster_point in cluster[1]:
                screePlotPoints[k-1] += pow(np.linalg.norm(cluster[0] - cluster_point), 2)

    plt.plot(testedKparams, screePlotPoints)
    plt.title("Screeplot")
    plt.xlabel("Amount of clusters")
    plt.xticks(np.arange(min(testedKparams), max(testedKparams)+1, 1.0))
    plt.ylabel("Intra cluster distance")
    plt.savefig("screeplot.png")
    plt.show()


if __name__ == "__main__":

    random.seed(0)

    # Load test dataset
    test_labels, test_data = \
            normalize_dataset(
                    load_labelled_dataset("../Datasets/dataset1.csv"), 
                    is_labelled=True)
            
    # load validation dataset
    val_labels, val_data = \
            normalize_dataset(
                    load_labelled_dataset("../Datasets/validation1.csv"), 
                    is_labelled=True)
    
    
    # print("Creating Screeplot...")
    # create_screeplot(test_data, 20)
    
    # optimal K=3, because this has the greatest "fall-off" in the screeplot.
    ctds = get_best_centroids(test_data, k=4, n_iterations=10)
    labeled_ctds = classify(test_data, test_labels, ctds)
    print(get_accuracy(val_data, val_labels, labeled_ctds))
        
