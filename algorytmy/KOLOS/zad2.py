
class Pierscien:
    def __init__(self, l):
        if not len(l):
            raise "Coś się popsuło i nie było mnie słuchać"
        self._data = l

    def __repr__(self):
        return repr(self._data)

    def __len__(self):
        return len(self._data)

    def __getitem__(self, i):
        return self._data[i]

    def next(self, iter):
        while True:
            print 
            if (iter == len(self._data) - 1):
                return self._data[0]
            if iter < len(self._data):
                return self._data[iter+1]
            else:
                while (iter > len(self._data)):
                    iter -= len(self._data)

    def before(self, iter):
        while True:
            if iter < len(self._data):
                return self._data[iter-1]
            if iter == len(self._data)-1:
                return self._data[iter-2]
            else:
                while (iter > len(self._data)):
                    iter -= len(self._data)

    def first(self):
        return self._data[0]

    def last(self):
        return self._data[-1]


# SPRAWDZENIE:
l = ['pierwszy', 'drugi', 'trzeci', 'ostatni!']
r = Pierscien(l)
print(r.first())
print(r.before(3))
print(r.before(0))
print(r.next(3))
