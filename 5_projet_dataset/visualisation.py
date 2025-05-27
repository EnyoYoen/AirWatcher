# Programme qui permet de visualiser les données du dataset measurements.csv.
# L'objectif est de voir l'évolution des mesures des 4 types de polluants au cours du temps et pour chaque capteur
# Le format du fichier est le suivant : TImestamp;SensorId;MeasurementType;Value
# Avec MeasurementType qui peut être PM10, SO2, NO2, O3
# Format de Timestamp : YYYY-MM-DD HH:MM:SS, ex : 2019-08-04 12:00:00

import pandas as pd
import time
import matplotlib.pyplot as plt
def plot_measurements(df):
    """
    Plot the measurements for each sensor and each pollutant type.
    Also computes and prints the variance for each pollutant type.
    Displays the variance for each pollutant on each sensor's figure.
    """
    # Convert Timestamp to datetime
    df['Timestamp'] = pd.to_datetime(df['Timestamp'], format='%Y-%m-%d %H:%M:%S')

    # Calculate and print variance for each pollutant type (global)
    variances = df.groupby('MeasurementType')['Value'].var()
    print("Variance for each pollutant type (global):")
    print(variances)

    # Create a pivot table to have sensors as columns and pollutants as rows
    pivot_df = df.pivot_table(index='Timestamp', columns=['SensorId', 'MeasurementType'], values='Value')

    # Plot each sensor's measurements for each pollutant type
    for sensor in pivot_df.columns.levels[0]:
        plt.figure(figsize=(8, 4))
        sensor_variances = {}
        for pollutant in pivot_df[sensor].columns:
            plt.plot(pivot_df.index, pivot_df[sensor][pollutant], label=pollutant)
            # Compute variance for this sensor and pollutant
            values = df[(df['SensorId'] == sensor) & (df['MeasurementType'] == pollutant)]['Value']
            sensor_variances[pollutant] = values.var()
        
        # Prepare variance text
        variance_text = "\n".join([f"{pollutant}: {sensor_variances[pollutant]:.2f}" for pollutant in sensor_variances])
        plt.gcf().text(0.98, 0.5, f"Variance:\n{variance_text}", fontsize=9, va='center', ha='right', bbox=dict(facecolor='white', alpha=0.7))

        plt.title(f'Measurements for Sensor {sensor}')
        plt.xlabel('Timestamp')
        plt.ylabel('Value')
        plt.legend()
        plt.grid()
        plt.tight_layout()
        plt.show(block=False)
        plt.pause(0.1)  # Force the figure to display immediately
        time.sleep(5)   # Wait before closing
        plt.close()

plot_measurements(pd.read_csv("C:/Users/dedel/Documents/Ecole/2024-2025/UML/TP/Code UML/5_projet_dataset/measurements.csv", sep=';'))