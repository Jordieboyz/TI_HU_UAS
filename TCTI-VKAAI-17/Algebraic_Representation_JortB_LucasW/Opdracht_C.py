"""
MNIST opdracht C: "Only Conv"      (by Marius Versteegen, 2021)

Bij deze opdracht gebruik je geen dense layer meer.
De output is nu niet meer een vector van 10, maar een
plaatje van 1 pixel groot en 10 lagen diep.

Deze opdracht bestaat uit vier delen: C1 tm C4 (zie verderop)


Opdracht C1; Voeg ALLEEN Convolution en/of MaxPooling2D layers toe aan het onderstaande model.":
        
    [
       keras.Input(shape=inputShape),
       
       layers.Conv2D(30, kernel_size=(5,5), padding="same"),
       layers.MaxPooling2D(pool_size=(2, 2)),
       
       layers.Conv2D(30, kernel_size=(5,5)),
       layers.MaxPooling2D(pool_size=(2, 2)),

       layers.Conv2D(num_classes, kernel_size=(5, 5), activation="softmax")
    ]
    
We hebben voor deze configuratie gekozen omdat in opdracht B de "eenvoudige" versie hiervan al voldoende werkte.
Met de precieze overname van opdreacht B kwamen we niet op een degelijke accuracy,
dus hebben we het model verdubbeld en om de layers te onderscheiden aan de eerste Conv2D
"same"-padding toegevoegd.

Hierna moesten we alleen nog de output layer naar de shape (1, 1, 10) vormen in 
de laatste Conv2D layer. Met deze configuratie haalde we na heel wat epochs de 0.98%.


Opdracht C2 && C3 && C4; verklaar op basis van de summary het aantal params, operaties en de output shapes;
Test accuracy: 0.9876999855041504 
Model: "sequential"
_________________________________________________________________
 Layer (type)                   Output Shape                Param #   
=================================================================
 conv2d (Conv2D)                (None, 28, 28, 30)          780       
                                                                 
 max_pooling2d (MaxPooling2D)   (None, 14, 14, 30)          0         
                                                                 
 conv2d_1 (Conv2D)              (None, 10, 10, 30)          22530     
                                                                 
 max_pooling2d_1 (MaxPooling2D) (None, 5, 5, 30)            0         
                                                                 
 conv2d_2 (Conv2D)              (None, 1, 1, 10)            7510      
=================================================================

Elementaire Operaties voor 1 sample worden berekend door:
    example:    kernel_size(KS)=(3, 3), inputShape(IS)=(28, 28, 1), outputShape(OS)=(26, 26, 32)
                
        KS[0][0] * IS[0][0]  +  KS[0][1] * IS[0][1] + KS[0][2] * IS[0][2] +
        KS[1][0] * IS[1][0]  +  KS[1][1] * IS[1][1] + KS[1][2] * IS[1][2] +
        KS[2][0] * IS[2][0]  +  KS[2][1] * IS[2][1] + KS[2][2] * IS[2][2]
    
    This is equal to: "9" * operations and "8" + opeartions for one kernel.
    Conclusion for "one sample": 
                amount_of_*_operations = np.prod(outputShape) * np.prod(kernel_size)
                amount_of_+_operations = np.prod(outputShape) * (np.prod(kernel_size) - 1)
                
conv2d (Conv2D)                
    Output Shape:   (None, 28, 28, 30)    
         De inputShape is (28, 28, 1). Aangezien de padding "same" is blijft de 
         shape hetzelfde. Er worden 30 filters gemaakt waardoor er een diepte van 30 ontstaat in deze shape.
         Dit maakt dus een shape van (28, 28, 30)
    
    Param #:        780
        ( filters * (  kernel_size * inputShape[2]) + bias
        (   30    * ((  5  *  5  ) *      1       ) + 30    = 780
     
    * operaties: 
        ( 28 * 28 * 30 ) * ( 5  *  5 ) = 588.000
            one sample = ( 28 * 28 ) * (5 * 5) = 19.600
     
    + operaties: 
        ( 28 * 28 * 30 ) * (( 5  *  5 ) - 1) = 564.480
            one sample = ( 28 * 28 ) * ((5 * 5) - 1) = 18.816

        
max_pooling2d (MaxPooling2D): 
    Output Shape:   (None, 14, 14, 30)    
         Max pooling met kernel_size (2,2) deelt de shape door 2. Daarom verandert 
         de shape van (28, 28) naar (14, 14). Hij doet echter niks met het aantal 
         filters, dus deze blijft gelijk.
    
    Param #:        0

                                                       
conv2d_1 (Conv2D):                                  
    Output Shape:   (None, 10, 10, 30)                  
         De inputShape is (14, 14, 30). Aangezien de padding niet "same" is 
         past de kernel maar 10 keer in de inputShape. Er worden 30 filters "gemaakt"
         Dit maakt dus een shape van (10, 10, 30).
      
    Param #:        22530  
        ( filters * (  kernel_size * inputShape[2]) + bias
        (   30    * ((  5  *  5  ) *      30       ) + 30    = 22530
     
    * operaties: 
        ( 10 * 10 * 30 ) * ( 5  *  5 ) = 75.000
            one sample = ( 10 * 10 ) * (5 * 5) = 2500
     
    + operaties: 
        ( 10 * 10 * 30 ) * (( 5  *  5 ) - 1) = 72.000
            one sample = ( 10 * 10 ) * ((5 * 5) - 1) = 2400

                                                              
max_pooling2d_1 (MaxPooling2D)   
    Output Shape:   (None, 5, 5, 30)     
         Max pooling met kernel_size (2,2) deelt de shape door 2. Daarom verandert 
         de shape van (10, 10) naar (5, 5). Hij doet echter niks met het aantal 
         filters, dus deze blijft gelijk.
    
    Param #:        0
                         
                             
 conv2d_2 (Conv2D)                               
    Output Shape:   (None, 1, 1, 10)              
         De inputShape is (5, 5, 30). De kernel met size (5, 5) past maar 1 keer 
         in de inputShape. Het aantal filters is gelijk aan het aantal "classes"
         Dit maakt dus een shape van (1, 1, 10).
      
    Param #:          7510   
        ( filters * (  kernel_size * inputShape[2]) + bias
        (   10    * ((  5  *  5  ) *      30       ) + 10    = 7510
     
    * operaties: 
        ( 1 * 1 * 30 ) * ( 5  *  5 ) = 750
            one sample = ( 1 * 1 ) * (5 * 5) = 25
     
    + operaties: 
        ( 1 * 1 * 30 ) * (( 5  *  5 ) - 1) = 720
            one sample = ( 1 * 1 ) * ((5 * 5) - 1) = 24

"""
import numpy as np
from tensorflow import keras
from tensorflow.keras import layers
import matplotlib.pyplot as plt
from matplotlib import pyplot
import matplotlib
import random
from MavTools_NN import ViewTools_NN

# Model / data parameters
num_classes = 10

# the data, split between train and test sets
(x_train, y_train), (x_test, y_test) = keras.datasets.mnist.load_data()

# Scale images to the [0, 1] range
x_train = x_train.astype("float32") / 255
x_test = x_test.astype("float32") / 255

print(x_test[0])

print("show image\n")
plt.figure()
plt.imshow(x_test[0])
plt.colorbar()
plt.grid(False)
plt.show()

# Conv layers expect images.
# Make sure the images have shape (28, 28, 1). 
# (for RGB images, the last parameter would have been 3)
x_train = np.expand_dims(x_train, -1)
x_test = np.expand_dims(x_test, -1)

print("x_train shape:", x_train.shape)
print(x_train.shape[0], "train samples")
print(x_test.shape[0], "test samples")

# convert class vectors to binary class matrices
y_train = keras.utils.to_categorical(y_train, num_classes)
y_test = keras.utils.to_categorical(y_test, num_classes)

# change shape 60000,10 into 60000,1,1,10  which is 10 layers of 1x1 pix images, which I use for categorical classification.
y_train = np.expand_dims(np.expand_dims(y_train,-2),-2)
y_test = np.expand_dims(np.expand_dims(y_test,-2),-2)

"""
Opdracht C1: 
    
Voeg ALLEEN Convolution en/of MaxPooling2D layers toe aan het onderstaande model.
(dus GEEN dense layers, ook niet voor de output layer)
Probeer een zo eenvoudig mogelijk model te vinden (dus met zo min mogelijk parameters)
dat een test accurracy oplevert van tenminste 0.98.

Voorbeelden van layers:
    layers.Conv2D(getal, kernel_size=(getal, getal))
    layers.MaxPooling2D(pool_size=(getal, getal))

Beschrijf daarbij met welke stappen je bent gekomen tot je model,
en beargumenteer elk van je stappen.

BELANGRIJK (ivm opdracht D, hierna):  
* Zorg er dit keer voor dat de output van je laatste layer bestaat uit een 1x1 image met 10 lagen.
Met andere woorden: zorg ervoor dat de output shape van de laatste layer gelijk is aan (1,1,10)
De eerste laag moet 1 worden bij het cijfer 0, de tweede bij het cijfer 1, etc.

Tip: Het zou kunnen dat je resultaat bij opdracht B al aardig kunt hergebruiken,
     als je flatten en dense door een conv2D vervangt.
     Om precies op 1x1 output uit te komen kun je puzzelen met de padding, 
     de conv kernal size en de pooling.
     
* backup eventueel na de finale succesvolle training van je model de gegenereerde weights file
  (myWeights.m5). Die kun je dan in opdracht D inladen voor snellere training.
  
  
Spoiler-mogelijkheid:
Mocht het je te veel tijd kosten (laten we zeggen meer dan een uur), dan
mag je de configuratie uit Spoiler_C.py gebruiken/kopieren.

Probeer in dat geval te beargumenteren waarom die configuratie een goede keuze is.
"""

def buildMyModel(inputShape):
    model = keras.Sequential(
        [
            keras.Input(shape=inputShape),
            layers.Conv2D(30, kernel_size=(5,5), padding="same"),
            layers.MaxPooling2D(pool_size=(2, 2)),
            layers.Conv2D(30, kernel_size=(5,5)),
            layers.MaxPooling2D(pool_size=(2, 2)),

            layers.Conv2D(num_classes, kernel_size=(5, 5), activation="softmax")
        ]
    )
    return model

model = buildMyModel(x_train[0].shape)
model.summary()

"""
Opdracht C2 && C3:
    
Kopieer bovenstaande model summary en verklaar bij elke laag met kleine berekeningen 
de Output Shape en het aantal parameters
    Zie bovenaan
"""

"""
Opdracht C4: 
    
Bij elke conv layer hoort een aantal elementaire operaties (+ en *).
* Geef PER CONV LAYER een berekening van het totaal aantal operaties 
  dat nodig is voor het klassificeren van 1 test-sample.
* Op welk aantal operaties kom je uit voor alle conv layers samen?
    zie bovenaan
"""

"""
## Train the model
"""

batch_size = 4096 # Larger means faster training, but requires more system memory.
epochs = 1000 # for now

bInitialiseWeightsFromFile = False # Set this to false if you've changed your model.

learningrate = 0.0001 if bInitialiseWeightsFromFile else 0.01

# We gebruiken alvast mean_squared_error ipv categorical_crossentropy als loss method,
# omdat straks bij opdracht D ook de afwezigheid van een cijfer een valide mogelijkheid is.
optimizer = keras.optimizers.Adam(lr=learningrate) #lr=0.01 is king
model.compile(loss='mean_squared_error',
              optimizer=optimizer,
              metrics=['categorical_accuracy'])

print("x_train.shape")
print(x_train.shape)

print("y_train.shape")
print(y_train.shape)

if (bInitialiseWeightsFromFile):
    model.load_weights("myWeights.h5"); # let's continue from where we ended the previous time. That should be possible if we did not change the model.
                                        # if you use the model from the spoiler, you
                                        # can avoid training-time by using "Spoiler_C_weights.h5" here.
try:
    model.fit(x_train, y_train, batch_size=batch_size, epochs=epochs, validation_split=0.2)
except KeyboardInterrupt:
    print("interrupted fit by keyboard")

"""
## Evaluate the trained model
"""

score = model.evaluate(x_test, y_test, verbose=0)
print("Test loss:", score[0])
print("Test accuracy:", ViewTools_NN.getColoredText(255,255,0,score[1]))

model.summary()

model.save_weights('myWeights.h5')

prediction = model.predict(x_test)
print(prediction[0])
print(y_test[0])

# summarize feature map shapes
for i in range(len(model.layers)):
	layer = model.layers[i]
	# check for convolutional layer
	if 'conv' not in layer.name:
		continue
	# summarize output shape
	print(i, layer.name, layer.output.shape)


print(x_test.shape)

# study the meaning of the filtered outputs by comparing them for
# multiple samples
nLastLayer = len(model.layers)-1
nLayer=nLastLayer
print("lastLayer:",nLastLayer)

baseFilenameForSave=None
x_test_flat=None
# ViewTools_NN.printFeatureMapsForLayer(nLayer, model, x_test_flat, x_test, 0, baseFilenameForSave)
# ViewTools_NN.printFeatureMapsForLayer(nLayer, model, x_test_flat, x_test, 1, baseFilenameForSave)
# ViewTools_NN.printFeatureMapsForLayer(nLayer, model, x_test_flat, x_test, 2, baseFilenameForSave)
# ViewTools_NN.printFeatureMapsForLayer(nLayer, model, x_test_flat, x_test, 3, baseFilenameForSave)
# ViewTools_NN.printFeatureMapsForLayer(nLayer, model, x_test_flat, x_test, 4, baseFilenameForSave)
# ViewTools_NN.printFeatureMapsForLayer(nLayer, model, x_test_flat, x_test, 6, baseFilenameForSave)
# ViewTools_NN.printFeatureMapsForLayer(nLayer, model, x_test_flat, x_test, 5, baseFilenameForSave)
# ViewTools_NN.printFeatureMapsForLayer(nLayer, model, x_test_flat, x_test, 7, baseFilenameForSave)
