import json
import sys 

def print_coloured(compression, avg, dither):
    print('\u001b[32;1m' + str(compression) + '\033[0m', end=' ')
    print('had a compression ratio of: ',  end='  ')
    if avg < 100:
        print('\u001b[32;1m' + str(avg) + '\033[0m', end='\t')
    else:
        print('\u001b[31;1m' + str(avg) + '\033[0m', end='\t')
    print(' with dither method: ', end='\t') 
    print('\u001b[32;1m' + str(dither) + '\033[0m')

def get_and_print_average_ratios(in_file):
    with open(in_file) as json_file:
        ratios = json.load(json_file)

    for compression in ratios:
        for dither in ratios[compression]:
            ratio_list = ratios[compression][dither]
            if not len(ratio_list) == 0:
                avg = sum(ratio_list) / len(ratio_list)
                print_coloured(compression, round(avg, 2), dither)

def get_arg(index):
    try:
        sys.argv[index]
    except IndexError:
        print('\u001b[31;1mERROR! You have to give a valid argument!\033[0m\n' +
              '\u001b[32;1m <.py file> <output_file>\033[0m\n')
        return ''
    else:
        return sys.argv[index]

if __name__ == "__main__":
    get_and_print_average_ratios(get_arg(1))