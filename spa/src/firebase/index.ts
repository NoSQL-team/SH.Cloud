import firebase from 'firebase/app';
import 'firebase/storage';

const firebaseConfig = {
  apiKey: "AIzaSyBJlYDTv45Qc9yDL6qROm0Yf0WceE0LYxE",
  authDomain: "noskool-sn.firebaseapp.com",
  projectId: "noskool-sn",
  storageBucket: "noskool-sn.appspot.com",
  messagingSenderId: "325503205410",
  appId: "1:325503205410:web:5b2f8913ffa1b6f645ca7b"
};

firebase.initializeApp(firebaseConfig);

const storage = firebase.storage();

export {
  storage,
  firebase as default
};
