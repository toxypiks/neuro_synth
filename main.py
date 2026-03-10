import pandas
import matplotlib.pyplot as plt
import torch as pt
import torch.nn as nn
from torch.utils.data import Dataset
from torch.utils.data import DataLoader


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
        return image_values, target


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
        self.optimizer = pt.optim.SGD(self.parameters(), lr=0.01)

    def forward(self, input):
        return self.model(input)


class NeuronalNetworkLearningOrganizer:
    def __init__(self, train_data, test_data):
        self.train_dataset = MnistDataset(train_data)
        self.test_dataset = MnistDataset(test_data)
        # hardcoded module
        self.classifier = Classifier()
        self.loss_fn = nn.BCELoss()

    def prepare(self):
        # vorverarbeitung
        print("TODO prepare")

    def _train_step(self):
        # just one train step of training
        print("TODO: train_step()")

    def train(self):
        # just one train step of training
        print("train")
        train_dataloader = DataLoader(self.train_dataset, batch_size=60, shuffle=True)
        n_epochs = 40
        for epoch in range(n_epochs):
            for images, targets in train_dataloader: # is doing 1000 loops
                outputs = self.classifier(images)
                # outputs save the computation path
                loss = self.loss_fn(outputs, targets)  # Compute the loss
                # Backward pass
                loss.backward()  # Compute gradients for all parameters

                # Update parameters
                self.classifier.optimizer.step()  # Apply the gradients to update model weights
                self.classifier.optimizer.zero_grad()  # Clear gradients for the next iteration


def main():
    train_data_path = "data/mnist_train.csv"
    test_data_path = "data/mnist_test.csv"
    organizer = NeuronalNetworkLearningOrganizer(
         train_data_path,
         test_data_path
     )

if __name__=="__main__":
    main()
