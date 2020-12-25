import * as React from "react";
import {FC, useState, useEffect} from 'react';
import {useSelector, useDispatch} from 'react-redux';
import {Redirect} from 'react-router-dom';

import {ProfileCard} from 'modules/ProfileCard';
import {SmallMoment} from 'components/SmallMoment';
import {APIUser} from 'utils/api';
import {IUserProfile, IUserStore} from 'types/user';
import {ioIError} from 'types/common';
import {IMoment} from 'types/moments';
import {setNoneAuth} from 'store/actionsCreators/userActionCreator';

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

  if (!match?.params.id) {
    useEffect(() => {
      APIUser.getMe(userStore.id).then(res => {
        if (!ioIError(res)) {
          setUserProfile(res);
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
          } else {
            setIsNotFound(true);
          }
        });
    }, []);
  }

	useEffect(() => {
		APIUser.getUser(userStore.id)
			.then(res => {
				if (!ioIError(res)) {
					setMoments(res.data);
				}
			})
	}, []);

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
            />
            <div className={'line'} />
            <div style={{fontSize: 'var(--text-sm)'}}>
              {!match?.params.id ? 'Ваши публикации: ' : 'Публикации пользователя: '}
            </div>
            <div className={'moments F-R-SP'} >
              {moments?.map((moment, index) => (
                <div className={'moment-wrapper'} key={index} >
                  <SmallMoment
                    likesQuantity={Number(moment.amount_likes)}
                    path={moment.attach}
                    isLiked={(moment.liked_users.indexOf(`i${userStore.id}`) === -1 ? false : true)}
                    id={Number(moment.post_id)}
                  />
                </div>
              ))}
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