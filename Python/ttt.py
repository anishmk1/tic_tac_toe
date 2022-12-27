
class Game:

    def __init__(self, x_o) -> None:
        self.player = x_o
        self.comp = not x_o        
        # print(" player {} comp {}".format(self.player, self.comp))


    def print_board(self):
        print()
        for i in range(3):
            for j in range(3):
                print("[ ] ", end="")
            print()
        print()




print("<<<<<< TIC_TAC_TOE >>>>>>>")

x_o = 0

while (True):
    g = Game(x_o)
    print("Press 1 - 9 to select a square")
    g.print_board()

    

    x_o = 0 if x_o else 1
    break