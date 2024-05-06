# Python Modules
from collections import Counter
import numpy as np
import sys
sys.path.append('../')

# Project Modules
from Datasets.import_dataset import normalize_dataset, load_labelled_dataset, load_dataset

'''
====================================================================================
=                           KNN functions                                      =
====================================================================================
'''
def classify(k, test_labels, test_data, data_point):
    '''
        Classify a specific data point.
    
        @param k                Amount of "nearest" neigbours
        @Param test_labels      Labels which we "mark" found neighbours with
        @Param test_data        Data which we test the data_point with
        @Param data_point       The 'to be tested' "uknown" data point
        
        @Return                 string
            String of the "predicted"/classified label.
    '''
    # Calculating Euclidean distances
    distances = np.array([ np.linalg.norm(test_data_point - data_point) for test_data_point in test_data ])

    # Evaluate the "nearest" neighbours and label them.
    k_nearest_neighbours = np.argpartition(distances, k)
    k_nearest_neighbours_labels = [test_labels[i] for i in k_nearest_neighbours[:k]]
    
    # Start resolving ties...
    label_occurrences = Counter(k_nearest_neighbours_labels)

    # We need at least two neighbours to have a tie
    if len(label_occurrences.most_common()) > 1:
        
        # check wether the second most occurences has the same amount of occurences as the first
        if label_occurrences.most_common()[0][1] == label_occurrences.most_common()[1][1]:
            
            # Re-Try with a lower K-value. Keep lowering k until we fixed the tie...
            return classify(k-1, test_labels, test_data, data_point)
    
    return label_occurrences.most_common()[0][0]

'''
====================================================================================
=                          Setup and Stats                                         =
====================================================================================
'''

def get_accuracy(k, val_data, val_labels, test_data, test_labels):

    succes=0
    for i, val_data_point in enumerate(val_data):

        # We return either True or False (1, 0), so add them either way.
        # Yes, I'm aware this is not so nice, but it's Python, I can do whatever Python let me do.
        # Check wether the classification of the selected data_point is what it supposed to be.
        succes += (classify(k, test_labels, test_data, val_data_point) == val_labels[i])
    
    # Save the accuracy of this specific K-value
    return succes / len(val_data) * 100 
    

def calculate_optimal_K(k, test_labels, test_data, val_labels, val_data, acc_list=None, curr_k=1):
    '''
        Recursively calculate the optimal K value. 
            Keep recursuing until all possible k-values are checked (len(validation_data))
    
        @param k                Amount of "nearest" neigbours
        @Param test_labels      Labels which we "mark" found neighbours with
        @Param test_data        Data which we test the data_point with
        @Param val_labels       Labels which we validate the classified data point with
        @Param val_data         Data which we validate the data_point with
        @Param acc_list         List of accuracy percentages to keep track of the most optimal k value
        @Param curr_k           Current value of K which isn being checked for accuracy
        
        @Return                     Int
            Most optimal K-value.
    '''
    if acc_list is None:
        acc_list = np.zeros(shape=(k,))
    
    if k == curr_k:
        return np.where(acc_list==np.max(acc_list))[0][0]  
    
    else:     
       
        # Save the accuracy of this specific K-value
        acc_list[curr_k] = get_accuracy(curr_k, val_data, val_labels, test_data, test_labels)
        
        # Recurse with incremented K value (until k == len(validation_data))
        return calculate_optimal_K(k, test_labels, test_data, val_labels, val_data, acc_list, curr_k+1)


if __name__ == "__main__":
   
    # Load and normalize "test"-dataset
    test_labels, test_data = \
            normalize_dataset(
                    load_labelled_dataset("../Datasets/dataset1.csv"), 
                    is_labelled=True)
            
    # Load and normalize "validation"-dataset
    val_labels, val_data = \
            normalize_dataset(
                    load_labelled_dataset("../Datasets/validation1.csv"), 
                    is_labelled=True)
    
    # Load and normalize "days"-dataset
    _, days_data = \
            normalize_dataset(
                    load_dataset("../Datasets/days.csv"))

    # Calculate the most optimal K value based on the test and validation dataset.
    # Start with k=1. Zero means no neighbours...
    # K = calculate_optimal_K(62, test_labels, test_data, 
    #                                 val_labels, val_data)
    
    print(test_labels)
    print(test_data)
    # classify the unlabelled dataset.
    print(f"Using K: 58 to perform classification\n")
    for data_point in days_data:
        print(
            "Predicted: "+str(classify(58, test_labels, test_data, data_point)))
        
