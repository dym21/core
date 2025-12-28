const KeyStorage = KeyStorageLibrary.KeyStorage;
const RsaOAEPKeyGenParams = KeyStorageLibrary.RsaOAEPKeyGenParams;
const c_oAscDigestType = KeyStorageLibrary.c_oAscDigestType;

function StorageManager() {
	this.keyStorage = new KeyStorage();
}
StorageManager.prototype.generateAsymmetricKey = function () {
	const oThis = this;
	return this.askMasterPassword().then(function (masterPassword) {
		return oThis.keyStorage.generateKey(new RsaOAEPKeyGenParams(c_oAscDigestType.SHA256), masterPassword.toUtf8(true));
	}).then(function (key) {
		oThis.keyStorage.addKeys([key]);
		return key;
	});
};
StorageManager.prototype.getMasterPassword = function () {
	let item = window.localStorage.getItem("masterPassword");
	if (item !== undefined) {
		return item;
	}
	item = window.sessionStorage.getItem("masterPassword");
	if (item !== undefined) {
		return item;
	}
	return null;
};
StorageManager.prototype.changeMasterPassword = function () {
	const oldMasterPassword = prompt("Enter Old Master Password");
	const newMasterPassword = prompt("Enter New Master Password");
	const oThis = this;
	return this.keyStorage.changeMasterPassword(oldMasterPassword.toUtf8(true), newMasterPassword.toUtf8(true)).then(function() {
		oThis.setMasterPassword(newMasterPassword);
	});
};
StorageManager.prototype.askMasterPassword = function () {
	let masterPassword = this.getMasterPassword();
	if (masterPassword === null) {
		masterPassword = prompt("Enter Master Password");
		this.setMasterPassword(masterPassword);
	}
	if (!this.keyStorage.isInit) {
		this.keyStorage.init();
	}
	return Promise.resolve(masterPassword);
};
StorageManager.prototype.clearMasterPassword = function() {
	localStorage.removeItem("masterPassword");
	sessionStorage.removeItem("masterPassword");
};
StorageManager.prototype.setMasterPassword = function(masterPassword) {
	this.clearMasterPassword();
	if (confirm("Save your master password in localStorage?")) {
		localStorage.setItem("masterPassword", masterPassword);
	} else {
		sessionStorage.setItem("masterPassword", masterPassword);
	}
};
StorageManager.prototype.getKeyByPublicKey = function (binaryData) {
	return this.keyStorage.getKeyByPublicKey(binaryData);
};
StorageManager.prototype.exportKeys = function () {
	return this.keyStorage.export();
};
StorageManager.prototype.importKeys = function (binaryData) {
	const oThis = this;
	return this.askMasterPassword().then(function (masterPassword) {
		return oThis.keyStorage.import(Uint8Array.fromBase64(binaryData), masterPassword.toUtf8(true));
	});
};
