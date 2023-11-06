def main():
    jar = Jar()
    print(str(jar.capacity))
    print(str(jar))
    jar.deposit(2)
    print(str(jar))
    jar.withdraw(1)
    print(str(jar))



class Jar:
    def __init__(self, capacity=12):
        if capacity < 1:
            raise ValueError('Wrong Capacity Value')
        self._capacity = capacity
        self._nCookies = 0

    def __str__(self):
        return "🍪" * self._nCookies

    def deposit(self, n):
        if self._nCookies + n > self._capacity:
            raise ValueError('Exceed Capacity')
        self._nCookies += n

    def withdraw(self, n):
        if self._nCookies - n < 0:
            raise ValueError('Not Enough Cookies')
        self._nCookies -= n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._nCookies


main()
