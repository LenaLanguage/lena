const fs = require('fs');
const path = require('path');

function findFiles(directory, extension) {
	fs.readdir(directory, { withFileTypes: true }, (err, files) => {
		if (err) {
			console.log(err);
			return;
		}
		files.forEach(file => {
			if (file.isDirectory()) {
				findFiles(path.join(directory, file.name), extension);
			} else if (file.name.endsWith(extension)) {
				console.log(path.join(directory, file.name));
			}
		});
	});
}

const args = process.argv.slice(2);

if (args.length > 1) {
	const directory = args[0];
	const extension = args[1];
	findFiles(directory, extension);
} else {
	console.log('[lena-i->scripts]: Usage: node find.js <directory> <extension>');
}
