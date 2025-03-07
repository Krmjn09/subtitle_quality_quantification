from vosk import Model, KaldiRecognizer
import wave

model = Model("vosk-model-small-en-us-0.15")
wf = wave.open("audio.wav", "rb")
rec = KaldiRecognizer(model, wf.getframerate())

transcript = []
while True:
    data = wf.readframes(4000)
    if len(data) == 0:
        break
    if rec.AcceptWaveform(data):
        result = rec.Result()
        transcript.append(json.loads(result)["text"])
        