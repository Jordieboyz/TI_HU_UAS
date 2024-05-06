import random
import copy

LUCAS="Lucas" 
STEPHAN="Stephan"
LENNARD="Lennard"
JASPER="Jasper"
MARTIJN="Martijn"
JORT="Jort"

names = [ LUCAS, STEPHAN, LENNARD, JASPER, MARTIJN, JORT ]

class student:
    def __init__(self, name, last_reviewed = None):
        self.name = name
        self.already_reviewed = dict(zip(names, [0]*len(names)))
        self.already_reviewed.pop(name)
    
    def __eq__(self, other):
        return self.name == str(other)
    
    def __repr__(self):
        string = "\n"
        string += self.name
        string += " : already reviewed: "
        string += str(self.already_reviewed)
        return string

class gilde:
    def __init__(self, student_list):
        self.students = [student(student_name) for student_name in student_list]
        self.n_students = len(student_list)
        
    def get_student(self, student):
        return self.students[self.students.index(student)]
    
    def __repr__(self):
        return str(self.students)


def update_indexes(gilde_, sprint_data):
    for p in sprint_data:
        for reviewed in sprint_data[p]:
            if reviewed:
                gilde_.get_student(p).already_reviewed[reviewed] += 1


def try_sequence(names_list, old_data):
    NEW = {}
    [NEW.setdefault(x, []) for x in names_list]

    global_names = copy.deepcopy(names_list)

    for student in names_list:

        local_names = copy.deepcopy(names)
    
        local_names.remove(student)
        for name in old_data[student][-3::]:
            if name in local_names:

                local_names.remove(name)
        
        while True:
            
            rand_student = random.choice(local_names)
            if rand_student is not student and rand_student in global_names:
                NEW[student].append(rand_student)
                global_names.remove(rand_student)
                break
            else:
                
                return try_sequence(names_list, old_data)
    return NEW


def add_and_control_dicts(dA, dB, noPop=False):
    res = {key: value + dB[key] for key, value in dA.items()}
    for item in res:
        if len(res[item]) > 4:
            res[item].pop(0)
    return res
    

TI_GILDE = gilde(names) 
new_sprint_data  = {
    LUCAS: [ LENNARD, JASPER ],
    STEPHAN: [ JASPER, LUCAS],
    LENNARD:[ STEPHAN, MARTIJN ],
    JASPER:[ MARTIJN, JORT ],
    MARTIJN:[ JORT, STEPHAN ],
    JORT:[ LUCAS, LENNARD ]
}

# Alleen voor 5B
# new_sprint_data  = {
#     LUCAS: [ JORT, STEPHAN],
#     STEPHAN: [ LENNARD, JORT],
#     LENNARD:[MARTIJN,LUCAS ],
#     JASPER:[ STEPHAN, LENNARD],
#     MARTIJN:[JASPER, LUCAS],
#     JORT:[  STEPHAN, JASPER]
# }
update_indexes(TI_GILDE, new_sprint_data)


# DEBUG:
random.seed(99)
n_sprints=3
for i in range(n_sprints):
    print("### SPRINT ", i+6) #?
    
    # Peer-Review partners for the first week (need to choose 2)
    r1_data = try_sequence(names, new_sprint_data)
    update_indexes(TI_GILDE, r1_data)
    
    restrictions_review_2 = add_and_control_dicts(new_sprint_data, r1_data)
    r2_data = try_sequence(names, restrictions_review_2)
    update_indexes(TI_GILDE, r2_data)
    
    # IMPORTANT SHUFFLE, make sure priority differs...
    random.shuffle(names)
    
    # Peer-Review partners for the second week (need to choose 2)
    restrictions_review_3 = add_and_control_dicts(restrictions_review_2, r2_data)
    r3_data = try_sequence(names, restrictions_review_3)
    update_indexes(TI_GILDE, r3_data)
    
    restrictions_review_4 = add_and_control_dicts(restrictions_review_3, r3_data)
    r4_data = try_sequence(names, restrictions_review_4)
    update_indexes(TI_GILDE, r4_data)

    # final 
    new_sprint_data = add_and_control_dicts(restrictions_review_4, r4_data)
    
    for st in new_sprint_data:
        print("{} gaat {} en {} reviewen".format(st, new_sprint_data[st][:2:], new_sprint_data[st][-2::]))

    print()
    
print(TI_GILDE)
    
