import os
import subprocess
import json
import sys
from av_ratios import get_and_print_average_ratios, get_arg

output_file = get_arg(1)
datasetDir = os.getcwd() + '/../images'

dFilter       = ['h', 'b', 'f', 't']
cMethods      = ['u', 'r', 'h']
            
ratios        = {'u' : {'halftone' : [], 'bayer' : [], 'floyd' : [], 'threshold' : []},
                 'r' : {'halftone' : [], 'bayer' : [], 'floyd' : [], 'threshold' : []},
                 'h' : {'halftone' : []}}

for compression in cMethods:
    for dither in ratios[compression]:
        for directory in os.listdir(datasetDir):

            path = str(datasetDir + "/" + directory)
            print("Working in path: " + str(path) + " with filter " + str(dither) + " and compression method: " + str(compression)) 

            for image in os.listdir(path):
                proc = subprocess.Popen(str("./main " + path + "/" + image + " -" + dither[0] + " -c -" + compression), stdout=subprocess.PIPE, shell=True)
                (out, err) = proc.communicate()
                try:
                    ratios[compression][dither].append(float(out.split()[-1]))
                except:
                    pass

with open(output_file, 'w') as outfile:
    json.dump(ratios, outfile, indent=2, sort_keys=False)

get_and_print_average_ratios(output_file)