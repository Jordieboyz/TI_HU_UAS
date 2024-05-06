import numpy as np

# Global variables (placeholders) to make sure we use the "same" 
# normalization formula for all the imported datasets.
Xmin_normalize=None
Xmax_normalize=None


def load_dataset(name, delimiter=';', usecols=[1,2,3,4,5,6,7]):
    '''
        Load a dataset, preferrably in .csv format (other file formats have not been tested)
        
        @param name             Name of the "to be loaded" dataset.
        @param delimiter        The string used to separate values.
        @Param usecols          Which columns to read, with 0 being the first.
        
        @Return                 ndarray 
            Data read from the desired file in array format.
    '''
    return np.genfromtxt(name, delimiter=delimiter, usecols=usecols, 
                         converters={5: lambda s: 0 if s == b"-1" else float(s), 
                                     7: lambda s: 0 if s == b"-1" else float(s)}
                         )


def load_labelled_dataset(name, delimiter=';', usecols=[1,2,3,4,5,6,7]):
    '''
        Load a dataset (preferrably in .csv format), 
            with desired labels to categorize the data.
        
        @param name             Name of the "to be loaded" dataset.
        
        @Return                 (ndarray, ndarray)
            Labels based on data from desired file, Data read from the desired file.
    '''
    dates = load_dataset(name, usecols=[0])
    
    data_labels = []
    for label in dates:
        
        # In this specific usecase, the whole year is not needed.
        # Just checking the month and day should be enough to label the data
        label %= 10000
        if label < 301 or label >= 1201:
            data_labels.append('winter')
        elif 301 <= label < 601:
            data_labels.append('spring')
        elif 601 <= label < 901:
            data_labels.append('summer')
        elif 901 <= label < 1201:
            data_labels.append('fall')

    return data_labels, load_dataset(name)

def normalize_dataset(dataset, is_labelled=False):
    '''
        Normalize a dataset.
        
        @param dataset          Dataset to be normalized.
        @Param is_labelled      Boolean wether the dataset is labelled or not.
        
        @Return                ( ndarray, nparray)
            Labels from the dataset, normalized data from dataset.
    '''
    global Xmin_normalize, Xmax_normalize
    
    if not is_labelled:
        labels, data = None, dataset
    else:
        labels, data = dataset
    
    # To make sure all the loaded datasets use the same Min-Max noramlization formula
    # Globally keep track if these values are set already.
    if not Xmin_normalize:
        Xmin_normalize = np.amin(data)
    if not Xmax_normalize:
        Xmax_normalize = np.amax(data)
        
    normalized_data = np.array([[((i - Xmin_normalize) / (Xmax_normalize - Xmin_normalize)) for i in day] for day in data]) 
    
    return labels, normalized_data