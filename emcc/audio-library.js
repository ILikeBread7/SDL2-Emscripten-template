mergeInto(LibraryManager.library, {
	"audioHelper": {
		"loadedMusicFiles": [],
		"loadedChunkFiles": [],
		"extractFileName": function(filepath) {
			var lastDot = filepath.lastIndexOf(".");
			if (lastDot < 0) {
				return filepath;
			}
			return filepath.substr(0, lastDot);
		},
		"supportedFormat": "",
		"getSupportedFormat": function() {
			if (!this._supportedFormat) {
				var audio = new Audio();
				if (audio.canPlayType("audio/ogg")) {
					this._supportedFormat = "ogg";
				} else {
					this._supportedFormat = "mp3";
				}
			}
			return this._supportedFormat;
		},
		"currentMusicVolume": 1,
		"currentChunkVolume": 1
	},
	"loadMusic": function(filepath) {
		filepath = _audioHelper.extractFileName(Pointer_stringify(filepath));
		var ext = _audioHelper.getSupportedFormat();
		var audio = new Audio(filepath+"."+ext);
		audio.volume = _audioHelper.currentMusicVolume;
		audio.loop = true;
		audio.load();
		_audioHelper.loadedMusicFiles.push(audio);
		return _audioHelper.loadedMusicFiles.length - 1;
	},
	"loadChunk": function(filepath) {
		filepath = _audioHelper.extractFileName(Pointer_stringify(filepath));
		var ext = _audioHelper.getSupportedFormat();
		var audio = new Audio(filepath+"."+ext);
		audio.volume = _audioHelper.currentChunkVolume;
		audio.load();
		_audioHelper.loadedChunkFiles.push(audio);
		return _audioHelper.loadedChunkFiles.length - 1;
	},
	"loadChunk__deps": ["audioHelper"],
	"playMusic": function(music) {
		_audioHelper.loadedMusicFiles[music].play();
	},
	"playMusic__deps": ["audioHelper"],
	"stopMusic": function() {
		for (var m in _audioHelper.loadedMusicFiles) {
			_audioHelper.loadedMusicFiles[m].pause();
			_audioHelper.loadedMusicFiles[m].currentTime = 0;
		}
	},
	"stopMusic__deps": ["audioHelper"],
	"playChunk": function(chunk) {
		_audioHelper.loadedChunkFiles[chunk].play();
	},
	"playChunk__deps": ["audioHelper"],
	"setMusicVolume": function(volume) {
		console.log('music ' + volume);
		_audioHelper.currentMusicVolume = volume;
		for (var m in _audioHelper.loadedMusicFiles) {
			_audioHelper.loadedMusicFiles[m].volume = volume;
		}
	},
	"setMusicVolume__deps": ["audioHelper"],
	"setChunkVolume": function(volume) {
		console.log('chunk ' + volume);
		_audioHelper.currentChunkVolume = volume;
		for (var c in _audioHelper.loadedChunkFiles) {
			_audioHelper.loadedChunkFiles[c].volume = volume;
		}
	},
	"setChunkVolume__deps": ["audioHelper"]
});