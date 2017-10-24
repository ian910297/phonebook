from faker import Faker
import sys

data_length = sys.argv[1] if len(sys.argv) >= 2 else 100
filename = sys.argv[2] if len(sys.argv) >= 3 else 'data.txt'
max_length = sys.argv[3] if len(sys.argv) >= 4 else 32

data_length = int(data_length)
max_length = int(max_length)

f = open(filename, 'w')
fake = Faker()
for _ in range(data_length):
    name = fake.name()
    while (len(name)>max_length):
        name = fake.name()
    f.write(fake.name() + '\n')
f.close()
