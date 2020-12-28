import * as React from "react";
import {FC, useState, useEffect, useRef} from 'react';
import {useSelector, useDispatch} from 'react-redux';
import {Redirect} from 'react-router-dom';

import {ProfileCard} from 'modules/ProfileCard';
import {APIUser} from 'utils/api';
import {IUserProfile, IUserStore} from 'types/user';
import {ioIError} from 'types/common';
import {IMoment} from 'types/moments';
import {setNoneAuth} from 'store/actionsCreators/userActionCreator';
import {Gallery} from 'components/Gallery';

import './profile-page.scss';

interface IProfilePageProps {
  match?: any
}

export const ProfilePage: FC<IProfilePageProps> = ({
  match
}: IProfilePageProps) => {

  const userStore: IUserStore = useSelector(state => state.user);
  const [userProfile, setUserProfile] = useState<IUserProfile>(null);
  const [isNoFound, setIsNotFound] = useState<boolean>(false);
  const dispatch = useDispatch();
  const [moments, setMoments] = useState<IMoment[]>(null);
  
  if (match?.params.id === userStore.id || !match?.params.id) {
    useEffect(() => {
      APIUser.getMe(userStore.id).then(res => {
        if (!ioIError(res)) {
          setUserProfile(res);
          APIUser.getUser(userStore.id)
            .then(res => {
              if (!ioIError(res)) {
                setMoments(res.data);
              }
            });
        } else {
          dispatch(setNoneAuth());
        }
      });
    }, []);
  } else {
    useEffect(() => {
      APIUser.getUserById(match?.params.id)
        .then((res) => {
          if (!ioIError(res)) {
            setUserProfile(res);
            setIsNotFound(false);
            APIUser.getUser(match?.params.id)
              .then(res => {
                if (!ioIError(res)) {
                  setMoments(res.data);
                }
              });
          } else {
            setIsNotFound(true);
          }
        });
    }, []);
  }

	return(
    <>
      {!userStore.refreshToken && <Redirect to={'/login'} />}
      {!isNoFound && (
        <div className={'profile-page'}>
          <div className={'content-wrapper'} >
            <ProfileCard
              momentsQuantity={0}
              name={userProfile?.nickname}
              photoPath={userProfile?.photo}
              firstName={userProfile?.firstname || ''}
              lastName={userProfile?.lastname || ''}
              userNumber={match?.params.id}
              ico_status={userProfile?.ico_status}
              status={userProfile?.status}
            />
            <div className={'line'} />
            <div style={{fontSize: 'var(--text-sm)'}}>
              {!match?.params.id ? 'Ваши публикации: ' : 'Публикации пользователя: '}
            </div>
            <div className={'moments'} >
              <Gallery moments={moments} />
            </div>
          </div>
        </div>
      )}
      {isNoFound && (
        <div>
          Not Found
        </div>
      )}
    </>
	);
}