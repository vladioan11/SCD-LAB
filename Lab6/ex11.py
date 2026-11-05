class Student:
    universitate= 'Dunarea de Jos'

    def __init__(self, nume, an):
        self.nume = nume
        self.an = an

    def afiseaza(self):
        print('Student %s anul %d Universitatea %s' % \
        (self.nume, self.an, Student.universitate))


student1 = Student("Popescu", 2)
student2 = Student("Ionesc", 1)
student3 = Student("Georgescu", 3)

student1.afiseaza()
student2.afiseaza()
student3.afiseaza()
