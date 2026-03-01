import pandas
import matplotlib.pyplot as plt
import torch as pt
import torch.nn as nn
from torch.utils.data import Dataset


class MnistDataset(Dataset):
    def __init__(self, data):
        df_data = pandas.read_csv(data, header=None)
        self.data = [(row.iat[0], row.iloc[1:].to_numpy()) for _, row in df_data.iterrows()]

    def __len__(self):
        return len(self.data)

    def __getitem__(self, index):
        label = self.data[index][0]
        target = pt.zeros((10))
        target[label] = 1.0
        image_values = pt.FloatTensor(self.data[index][1]) / 255.0
        return label, image_values, target


class Classifier(nn.Module):
    def __init__(self):
        super(Classifier, self).__init__()
        self.model = nn.Sequential(
            nn.Linear(784, 200),
            nn.Sigmoid(),
            nn.Linear(200, 10),
            nn.Sigmoid()
        )
        self.loss_function = nn.MSELoss()
        self.optimiser = pt.optim.SGD(self.parameters(), lr=0.01)

    def forward(self, input):
        return self.model(input)


class NeuronalNetworkLearningOrganizer:
    def __init__(self, train_data, test_data):
        self.train_dataset = MnistDataset(train_data)
        self.test_dataset = MnistDataset(test_data)
        # hardcoded module
        self.classifier = Classifier()

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
