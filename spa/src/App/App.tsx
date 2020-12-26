import * as React from "react";
import {
	BrowserRouter as Router,
  Route,
  browserHistory
} from 'react-router-dom';
import {FC} from 'react';
import {useDispatch} from 'react-redux';

import {Header} from 'modules/header'
import {
  LoginPage,
  MainPage,
  ProfilePage,
  RecomendedPage,
  MomentPage,
  ProfileSettingsPage
} from 'pages';
import {setUserAuths} from 'store/actionsCreators/userActionCreator';
import {useModalWindow} from 'hooks/useModalWindow';
import {MomentCreatePopup} from 'modules/MomentCreatePopup';
import GuthubIcon from 'assests/app/icons/github.svg';

import './app.scss'

export const App: FC = () => {

  const dispatch = useDispatch();
  if (localStorage.getItem('login')) {
    dispatch(setUserAuths({
      login: localStorage.getItem('login'),
      refreshToken: localStorage.getItem('refreshToken'),
      id: Number(localStorage.getItem('id'))
    }))
  }

  const {toggleModal, isOpen, closeWindow} = useModalWindow();

  return(
    <>
      <Router history={browserHistory} >
        <Header toggleModal={toggleModal} closeWindow={closeWindow} />
        <div>
          <Route path="/login" exact render={() => <LoginPage />} />
          <Route path="/profile" exact render={() => <ProfilePage />} />
          <Route path="/profile/:id" exact render={(props) => <ProfilePage {...props}/>} />
          <Route path="/profile-settings" exact render={() => <ProfileSettingsPage />} />
          <Route path="/" exact render={() => <MainPage />} />
          <Route path="/recomended" exact render={() => <RecomendedPage />} />
          <Route path="/moment/:id" exact render={(props) => <MomentPage {...props} />} />
          {isOpen && (
            <MomentCreatePopup 
              toggleModal={toggleModal}
            />
          )}
          <a href="https://github.com/NoSQL-team" className={'github-icon'} target="blank">
            <GuthubIcon />
          </a>
        </div>
      </Router> 
    </>
  );
}
