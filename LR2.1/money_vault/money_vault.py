from banknote.banknote import Banknote


class MoneyVault:
    def __init__(self, money_vault: dict[Banknote, int]) -> None:
        self.__money_vault: dict[Banknote, int] = money_vault

    @property
    def money_vault(self) -> dict:
        return self.__money_vault

    def get_money(self, money_value: int) -> None:
        self.__money_vault = dict(sorted(self.__money_vault.items()))
        possible_opt = dict()
        available_best_sum, rest_sum = 0, money_value
        for banknote, amount in self.__money_vault.items():
            best_amount_available = min(rest_sum // banknote.value, amount)
            possible_opt[banknote] = best_amount_available
            available_best_sum += banknote.value * best_amount_available
            rest_sum -= banknote.value * best_amount_available
        if available_best_sum != money_value:
            raise ValueError
        else:
            for banknote in self.__money_vault.keys():
                self.__money_vault[banknote] -= possible_opt[banknote]

    def __str__(self):
        return_str = "Available banknotes:\n"
        for banknote, amount in self.__money_vault.items():
            return_str += f"{banknote} BYN - {amount}\n"
        return return_str

