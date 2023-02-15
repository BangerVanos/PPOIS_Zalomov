import unittest
from plastic_card.plastic_card import PlasticCard
from card_account.card_account import CardAccount
import regex as re


class AtmTest(unittest.TestCase):
    def setUp(self) -> None:
        self.card_account: CardAccount = CardAccount("abba", 1000.33)
        self.plastic_card: PlasticCard = PlasticCard(card_id="4000500060007000", pin="5678", card_acc=self.card_account,
                                                     expiration_date="09/25", is_blocked=False)

    def test_balance(self):
        self.assertEqual(self.card_account.balance, 1000.33)

    def test_card_account_id(self):
        self.assertEqual(self.card_account.acc_id, "abba")

    def test_balance_add(self):
        self.card_account.bal_add(100.22)
        self.assertEqual(self.card_account.balance, 1100.55)

    def test_balance_sub(self):
        self.card_account.bal_sub(100.22)
        self.assertEqual(self.card_account.balance, 900.11)

    def test_card_id(self):
        self.assertEqual(self.plastic_card.card_id, "4000500060007000")

    def test_pin(self):
        self.assertEqual(self.plastic_card.check_pin("5678"), True)

    def test_incorrect_pin(self):
        self.assertEqual(self.plastic_card.check_pin("5999"), False)

    def test_block(self):
        self.plastic_card.is_blocked = True
        self.assertEqual(self.plastic_card.is_blocked, True)
        self.plastic_card.is_blocked = False
        self.assertEqual(self.plastic_card.is_blocked, False)

    def test_phone_regular_exp(self):
        self.assertEqual(re.fullmatch(r"\+375(29|33|25|44|17|29)\d{7}", "+3754545612344"), None)


if __name__ == '__main__':
    unittest.main()
