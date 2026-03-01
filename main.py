import pandas
import matplotlib.pyplot as plt

class NeuronalNetworkLearningOrganizer:
    def __init__(self, train_data, test_data):
        df_train = pandas.read_csv(train_data, header=None)
        df_test = pandas.read_csv(test_data, header=None)
        self.train_data = df_train #csv lesen
        self.test_data = df_test
        print("TODO")

    def prepare(self):
        # vorverarbeitung
        print("TODO prepare")

    def _train_step(self):
        # just one train step of training
        print("TODO: train_step()")

    def train(self):
        # learning of neuronal network
        # use self.train in loop
        print("TODO: train()")



def main():
    train_data_path = "data/mnist_train.csv"
    test_data_path = "data/mnist_test.csv"
    organizer = NeuronalNetworkLearningOrganizer(
         train_data_path,
         test_data_path
     )

if __name__=="__main__":
    main()
