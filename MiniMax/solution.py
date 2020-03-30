from random import randint

class Game:
    # this class maintains the information about the game state
    def __init__(self, total_sticks):
        self.sticks = total_sticks
    
    def get_sticks(self):
        return self.sticks

    def decrease_sticks(self, sticks):
        self.sticks -= sticks

    def is_over(self):
        return self.sticks == 1
    pass
    

class Player:
    # this class represents the AI player class
    def __init__(self, name):
        self.name = name

    def __repr__(self):
        return "AI " + str(self.name)
    
    def check_move(self, sticks_left, turn, alpha, beta, depth):
        # print(turn, alpha, beta)
        # maximizing move
        if turn == self.name:
            # base case
            if sticks_left == 1:
                return -1
            if depth >= 20:
                if sticks_left > 5:
                    return -0.5
                elif sticks_left == 5:
                    return -1
                elif sticks_left < 5:
                    return 1   

            best_score = alpha            
            turn = 1 if turn == 2 else 2
            for i in range(1, 4):
                sticks_left -= i
                if sticks_left > 0:
                    score = self.check_move(sticks_left, turn, best_score, beta, depth+1)
                    if best_score is None or best_score < score:
                        best_score = score
                        if beta is not None and beta <= best_score:
                            return best_score
                sticks_left += i
            return best_score

        # minimizing move
        else:
            # base case
            if sticks_left == 1:
                return 1  
            if depth >= 20:
                if sticks_left > 5:
                    return 0.5
                elif sticks_left == 5:
                    return 1
                elif sticks_left < 5:
                    return -1    
        
            best_score = beta
            turn = 1 if turn == 2 else 2
            for i in range(1, 4):
                sticks_left -= i
                if sticks_left > 0:
                    score = self.check_move(sticks_left, turn, alpha, best_score, depth+1)
                    if best_score is None or best_score > score:
                        best_score = score
                        if alpha is not None and best_score <= alpha:
                            return best_score
                sticks_left += i
            return best_score  

    
    def best_move(self, sticks_left):
        best_ans = None
        alpha = None
        beta = None
        depth = 0
        turn = 1 if self.name == 2 else 2

        for i in range(1, 4):
            sticks_left -= i
            if sticks_left > 0:
                score = self.check_move(sticks_left, turn, alpha, beta, depth)
                if alpha is None or alpha < score:
                    best_ans = i
                    alpha = score
            sticks_left += i
        
        return best_ans
        pass
    pass



def take_input(question, low_limit = None, high_limit = None):
    # since user input is unpredictable hence this function is implemented for taking in appropriate input
    while True:
        try:
            num = int(input(question))

            if low_limit is not None and high_limit is not None and (num < low_limit or num > high_limit):
                raise ValueError('')

            return num

        except ValueError:
            print("That number does not fall in the given range")
        
        except NameError:
            print("That's not a valid input")
    pass



def Play_Game(Sticks_Game, Players):
    # the game starts here
    turn = randint(1,2)

    while not Sticks_Game.is_over():
        move = None
        if "{}".format(Players[turn]).count("User"):
            move = take_input("{}, enter number of sticks you want to pick, from 1 to 3\n".format(Players[turn]), 1, 3)
        else:
            move = Players[turn].best_move(Sticks_Game.get_sticks())

        print("{} chose {} sticks to reduce.".format(Players[turn], move))
        Sticks_Game.decrease_sticks(move)
        if Sticks_Game.get_sticks() < 1:
            break

        turn = 1 if turn == 2 else 2
    
    print("{} looses the game!".format(Players[turn]))
    pass



if __name__ == "__main__":
    # setting up the game particularly number of sticks required
    total_sticks = take_input("How many sticks do you want to have in the game?\n")
    Sticks_Game = Game(total_sticks)
    
    # setting up the type of game user wants
    type_of_game = take_input("What type of game setting do you want?\n1: AI vs AI\n2: AI vs User\n3: User vs User\nEnter the corresponding number.\n", 1, 3)
    Players = {}
    if type_of_game == 1:
        Players = {
            1: Player(1),
            2: Player(2)
        }
    elif type_of_game == 2:
        Players = {
            1: Player(1),
            2: "User 1"
        }
    else:
        Players = {
            1: "User 1",
            2: "User 2"
        }
    # starting the game
    Play_Game(Sticks_Game, Players)
    pass
