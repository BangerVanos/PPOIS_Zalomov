from card_account.card_account import CardAccount


class PlasticCard:
    def __init__(self, card_id: str, pin: str, card_acc: CardAccount, is_blocked: bool) -> None:
        self.__card_id: str = card_id
        self.__pin: str = pin
        self.__card_acc: CardAccount = card_acc
        self.__is_blocked: bool = is_blocked

    @property
    def card_acc(self) -> CardAccount:
        return self.__card_acc

    @property
    def is_blocked(self) -> bool:
        return self.__is_blocked

    @is_blocked.setter
    def is_blocked(self, new_block_status: bool):
        self.__is_blocked = new_block_status

    def check_pin(self, pin: str) -> bool:
        return self.__pin == pin

    def __delete__(self, instance):
        del self

    def __str__(self) -> str:
        return f"Card ID: {self.__card_id}" \
               f"Balance: {self.__card_acc.balance}"

