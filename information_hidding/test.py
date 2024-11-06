import numpy as np

secret_message = 'Hello, World!'
secret_bits = np.unpackbits(np.frombuffer(
    secret_message.encode(), dtype=np.uint8))
print('secret_bits: ', secret_bits)

np.packbits(secret_bits).tobytes().decode()
print('secret_message: ', secret_message)

