from plastic_card.plastic_card import PlasticCard
from money_vault.money_vault import MoneyVault
import exceptions.exceptions as exc


class ATM:
    def __init__(self, money_vault: MoneyVault, plastic_card: PlasticCard):
        self.__money_vault = money_vault
        self.__plastic_card = plastic_card

    @property
    def get_card_balance(self) -> float:
        if self.__plastic_card.is_blocked:
            raise exc.CardIsBlocked
        return self.__plastic_card.card_acc.balance

    @property
    def get_card_block_status(self) -> bool:
        return self.__plastic_card.is_blocked

    def block_card(self):
        self.__plastic_card.is_blocked = True

    def check_card_pin(self, pin: str):
        return self.__plastic_card.check_pin(pin)

    def get_cash_money(self, money_value: int):
        if self.__plastic_card.is_blocked:
            raise exc.CardIsBlocked
        if isinstance(money_value, int):
            if money_value > self.__plastic_card.card_acc.balance:
                raise exc.NotEnoughMoney
            try:
                self.__money_vault.get_money(money_value)
            except exc.NoAvailableMoneyConfig:
                raise exc.NoAvailableMoneyConfig
            else:
                self.__plastic_card.card_acc.bal_sub(money_value)
        else:
            raise ValueError

    def custom_operation(self, money_value: float):
        if self.__plastic_card.is_blocked:
            raise exc.CardIsBlocked
        if isinstance(money_value, float):
            try:
                self.__plastic_card.card_acc.bal_sub(money_value)
            except exc.NotEnoughMoney:
                raise exc.NotEnoughMoney
