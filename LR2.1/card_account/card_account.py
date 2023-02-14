import exceptions.exceptions as exc


class CardAccount:
    def __int__(self, balance: float, acc_id: int) -> None:
        self.__balance: float = balance
        self.__acc_id: int = acc_id

    @property
    def balance(self) -> float:
        return self.__balance

    def bal_add(self, value: float):
        self.__balance += value

    def bal_sub(self, value: float):
        if self.__balance < value:
            raise exc.NotEnoughMoney
        self.__balance -= value

    @property
    def acc_id(self) -> int:
        return self.__acc_id

    def __delete__(self, instance):
        del self

    def __str__(self):
        return f"Account ID: {self.__acc_id}\n" \
               f"Account Balance: {self.__balance}"
