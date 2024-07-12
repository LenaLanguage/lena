const fs = require('fs');
const path = require('path');

const filesToDelete = process.argv.slice(2);

filesToDelete.forEach(file => {
    try {
        if (fs.existsSync(file)) {
            fs.unlinkSync(file);
        }
    } catch (err) {
    }
})