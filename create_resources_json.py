import os
import json

# Directory path
dir_path = "res/sounds/kiza_kana/"

# Collect all wav filenames
filenames = [f for f in os.listdir(dir_path) if f.endswith('.wav')]

# Extract sound keys and create the dictionary
sounds_dict = {}
for filename in filenames:
    # Extract the sound key (last part before .wav) from filename
    sound_key = filename.split("_")[-1].replace(".wav", "")

    # Construct the value (relative path) for the dictionary
    sound_value = "kiza_kana/" + filename
    sounds_dict[sound_key] = sound_value

# Create final JSON dictionary
final_dict = {"sounds": sounds_dict}

# Write to resources.json
with open("resources.json", "w") as file:
    json.dump(final_dict, file, indent=4)

print("resources.json created successfully")
