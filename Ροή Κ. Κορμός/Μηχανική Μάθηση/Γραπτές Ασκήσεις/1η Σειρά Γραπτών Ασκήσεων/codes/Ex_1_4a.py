import numpy as np

# Define the activation function
def activation_function(x):
    return 1 if x >= 0 else 0

# Perceptron weight update rule
def update_weights(weights, sample, learning_rate, expected_output, actual_output):
    return weights + learning_rate * (expected_output - actual_output) * sample

# Initialize weights and other parameters
weights = np.array([1, 0, 0, 0])
learning_rate = 1  # Typically set to 1 for basic perceptron

# Define the samples and their classes
samples = np.array([[4, 3, 6], [2, -2, 3], [1, 0, -3], [4, 2, 3]])
classes = np.array([0, 1, 1, 0])  # 0 for CN (negative class), 1 for CP (positive class)

# Record keeping
steps = []

# Train the perceptron
converged = False
iteration = 0
while not converged:
    converged = True  # Assume it has converged until proven otherwise
    for i, sample in enumerate(samples):
        iteration += 1
        # Add the bias term to the sample
        sample_with_bias = np.insert(sample, 0, 1)  # Bias input is always 1
        # Calculate the perceptron output
        activation_input = np.dot(weights, sample_with_bias)
        output = activation_function(activation_input)
        expected_output = classes[i]
        # Check if the perceptron output matches the expected output
        correct_classification = output == expected_output
        if not correct_classification:
            converged = False
            # Update the weights
            new_weights = update_weights(weights, sample_with_bias, learning_rate, expected_output, output)
            # Determine the classification result
            classification_result = 'FN' if expected_output == 1 else 'FP'  # False Negative or False Positive
        else:
            new_weights = weights.copy()
            # Determine the classification result
            classification_result = 'TP' if expected_output == 1 else 'TN'  # True Positive or True Negative
        
        # Record the step
        steps.append({
            'iteration': iteration,
            'sample': sample_with_bias,
            'output': output,
            'classification_result': classification_result,
            'weight_change': new_weights - weights,
            'updated_weights': new_weights
        })
        weights = new_weights  # Update the weights for the next iteration

# Output the steps for review
print("Perceptron Training Steps:\n")
print("{:<10} {:<20} {:<10} {:<15} {:<20} {:<20}".format(
    'Iteration', 'Sample (with bias)', 'Output', 'Classification', 'Weight Change', 'Updated Weights'))
print("-" * 95)

for step in steps:
    print("{:<10} {:<20} {:<10} {:<15} {:<20} {:<20}".format(
        step['iteration'],
        str(step['sample']),
        step['output'],
        step['classification_result'],
        str(step['weight_change']),
        str(step['updated_weights'])))
