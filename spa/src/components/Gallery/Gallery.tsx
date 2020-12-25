import * as React from "react";
import {ReactElement, useState, FC, useEffect, useRef} from 'react';
import {useSelector} from 'react-redux';
import {Link} from 'react-router-dom';

import {isMobile} from 'react-device-detect'
import LikedIcon from 'assests/moment/icons/liked.svg';
import UnlikedIcon from 'assests/moment/icons/unliked.svg';
import {IUserStore} from 'types/user';
import {IMoment} from 'types/moments';

import './gallery.scss'

interface GalleryProps {
  moments: IMoment[];
}

export const Gallery: FC<GalleryProps> = ({
  moments
}: GalleryProps): ReactElement => {

  const [isHover, setIsHover] = useState<boolean>(false);
  const userStore: IUserStore = useSelector(state => state.user);
  const galleryRef = useRef(null);

  useEffect(() => {
    const getVal = (elem, style) => { return parseInt(window.getComputedStyle(elem).getPropertyValue(style)); };
    const getHeight = (item) => { return item.querySelector('.content').getBoundingClientRect().height; };
    const resizeAll = () => {
        const altura = getVal(galleryRef.current, 'grid-auto-rows');
        const gap = getVal(galleryRef.current, 'grid-row-gap');
        galleryRef.current.querySelectorAll('.gallery-item').forEach(function (item: HTMLDivElement) {
            var el = item;
            el.style.gridRowEnd = "span " + Math.ceil((getHeight(item) + gap) / (altura + gap));
        });
    };
    galleryRef.current.querySelectorAll('img').forEach(function (item) {
        if (!item.complete) {
          item.addEventListener('load', function () {
              var altura = getVal(galleryRef.current, 'grid-auto-rows');
              var gap = getVal(galleryRef.current, 'grid-row-gap');
              var gitem = item.parentElement.parentElement;
              gitem.style.gridRowEnd = "span " + Math.ceil((getHeight(gitem) + gap) / (altura + gap));
          });
        }
    });    
    resizeAll();
  }, [moments]);

  return(
    <div className={'gallery'} ref={galleryRef}>
      {moments?.map((moment, index) => (
        <div className={'gallery-item'} key={index}>
          <div className={'content'}>
            <Link to={`/moment/${moment.post_id}/`} >
              <img src={moment.attach} />
            </Link>
          </div>
        </div>
      ))}
    </div>
  );
}
